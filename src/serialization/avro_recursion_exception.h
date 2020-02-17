// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include <exception>
#include <stdexcept>

#ifndef TC_SERIALIZATION_AVRO_RECURSION_EXCEPTION_H_
#define TC_SERIALIZATION_AVRO_RECURSION_EXCEPTION_H_

namespace tc_serialization {

class AvroRecursionException : public std::runtime_error {

public:
  // Constructors
  AvroRecursionException() :
    std::runtime_error("Cannot serialize record to JSON with recursive datatype defined."
                       " See https://issues.apache.org/jira/browse/AVRO-1635.") {};
};

}  // namespace tc_serialization

#endif  // TC_SERIALIZATION_AVRO_RECURSION_EXCEPTION_H_
