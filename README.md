# Dependency Installation
We install dependencies into `/usr/local/`, and the below instructions assume that.

## Installing Avro C++
The following will install Avro C++ bindings (headers, libraries, and the code generation tool).
```sh
sudo apt-get install libboost-dev libboost-filesystem-dev libboost-system-dev libboost-program-options-dev libboost-iostreams-dev
wget http://archive.apache.org/dist/avro/avro-1.8.2/cpp/avro-cpp-1.8.2.tar.gz
tar xvzf avro-cpp-1.8.2.tar.gz
cd avro-cpp-1.8.2
./build.sh test # This should succeed, otherwise we want to bail
sudo ./build.sh install
```

## Installing librdkafka C++
The librdkafka includes both C and C++ bindings.  Here is how to install it:
```sh
git clone https://github.com/edenhill/librdkafka.git
cd librdkafka/
./configure
make
sudo make install
```

For tc-in-a-box and within the cluster, we currently are tracking the release `v0.11.4`, which is tagged in the repo.

## Installing Google test (Unit testing Framework)
The Google Test framework is used to drive our unit tests.  Here is how to install it:
```sh
git clone https://github.com/google/googletest.git
mkdir -p googletest/build
cd googletest/build
cmake ..
make
sudo make install
```

## Installing Boost Log
While we use a very basic logging interface, under the hood we are using the somewhat complex boost log library.  Fortunately, this is very easy to install.  In the case of Ubuntu machines, we simply install the library through apt.

# Installation

## Installing Schema C++ Generated Code
Generating the C++ bindings for the schema is done within the ta3-serialization-schema project.  Here is how to generate the code:
```sh
# Set SCHEMA_PROJ to the path where your clone of ta3-serialization-schema lives!
SCHEMA_PROJ=~/ta3-serialization-schema
cd $SCHEMA_PROJ
sudo mvn compile -Pcpp
```
This will install the header file containing the objects into `/usr/local/include/tc_schema/cdm.h`

## Installing the API from the repo
You will need to have autoconf and libtools installed for this.

The serialization API has been compiled into a library for the TCCDMDatum type and Avro's generic type.  To install these, run the following:
```sh
# Set CPP_PROJ to the path where your clone of ta3-api-bindings-cpp lives!
CPP_PROJ=~/ta3-api-bindings-cpp
cd $CPP_PROJ
./autogen.sh
mkdir build && cd build
../configure
make
sudo make install
```

# Running the unit tests
You can run the unit test suite as follows:
```sh
cd build
make check
```

Each test file contains multiple tests, although the above will return a summary of whether each file passed or failed.  To see individual test cases within the file, simply run the actual unit test:
```sh
cd build/test
TARGET_TEST=<test_binary>
./${TARGET_TEST}
```

# Using the APIs
APIs are still subject to change, although we will try to keep them as constant as possible.

## Serialization
Here are a few quick notes... more thorough documentation coming soon:
 * We leverage class templates for our serializers and deserializers.
 * Currently, **only** specific types (i.e. generated code from the schema) are supported by the API.  Avro's Generic type can be added if that is desired, but getting a full set of feautres working for one type is the priority.
 * Currently, **only** the TCCDMDatum type is supported in the built-in library.  Other types can be supported, but they are not pre-compiled into the TA3 library.
 * The API leans on C++11 features, including `unique_ptr` and move constructors.
 * Serialization and deserialization to buffers and json are done using the `AvroGenericSerializer` and `AvroGenericDeserializer` classes.
 * Serialization and deserialization to binary files are done using the `AvroGenericFileSerializer` and `AvroGenericFileDeserializer` classes.  Note that these are separate classes, unlike the Java and Python APIs.

## Logging
There are two steps to using the logging library:
 * Include the `tc_util/logger.h` header file.
 * Intialize through the `tc_util::Logger::init` static method, optionally passing in a config file.  There is an example config file in `conf/logconfig.ini`, and we recommend using this config file at least as a baseline to set up your logging config.
 * Do your logging!  There are 6 levels supported, and log messages are passed through streams to each one.  Log messages are not built unless the severity level of the message is higher than the configured severity level for logging.  Below are examples:
  * `LOG_TRACE << "This is a trace level log message.";`
  * `LOG_DEBUG << "This is a debug level log message.";`
  * `LOG_INFO << "This is an info level log message.";`
  * `LOG_WARN << "This is a warning level log message.";`
  * `LOG_ERROR << "This is an error level log message.";`
  * `LOG_FATAL << "This is a fatal level log message.";`

There is a limitation with the current logging approach if one wants to use a config file and sink filters:
 * Generally speaking about the logging data flow in boost logging, the global filter and the sink filter are serialized with the global filter coming first.
 * Sink filters allow for more control, since you can have more than one sink, and you may want to filter different things for different sinks (e.g. allow max verbosity to a log file, but only debug level to console).
 * The global filter can be changed from the setting in the config file at runtime, but the sink filters set by the config file cannot be changed at runtime.

If one uses a config file, this allows for setting the sink filters to the highest level allowed in the config, and then one can modify the log level at runtime by changing the global level.  This does not allow for as much control as having no filter on the global level and changing sink filters at run time, but it is better than only setting the global filter and not touching the sink filters in terms of flexibility.

According to https://sourceforge.net/p/boost-log/discussion/710021/thread/32844141/ this may change in the next major revision of boost logging, and we can revisit this limitation if that comes out.
