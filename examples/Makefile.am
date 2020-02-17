# Copyright (c) 2020 Raytheon BBN Technologies Corp.
# See LICENSE.txt for details.

noinst_PROGRAMS = producer_example consumer_example kafka_client_demo seeking_pull_consumer_example

AM_CXXFLAGS = -I$(srcdir)/../src $(CONFIGURE_CXXFLAGS) -DBOOST_LOG_DYN_LINK

producer_example_SOURCES = producer_example.cc
producer_example_LDADD = ../src/libtcta3cpp.la $(AVROCPP_LIBS) $(BOOST_LOG_LIBS) $(RDKAFKACPP_LIBS) $(LDADD)
consumer_example_SOURCES = consumer_example.cc
consumer_example_LDADD = ../src/libtcta3cpp.la $(AVROCPP_LIBS) $(BOOST_LOG_LIBS) $(RDKAFKACPP_LIBS) $(LDADD)
kafka_client_demo_SOURCES = kafka_client_demo.cc
kafka_client_demo_LDADD = ../src/libtcta3cpp.la $(AVROCPP_LIBS) $(BOOST_LOG_LIBS) $(RDKAFKACPP_LIBS) $(LDADD) -lpthread
seeking_pull_consumer_example_SOURCES = seeking_pull_consumer_example.cc
seeking_pull_consumer_example_LDADD = ../src/libtcta3cpp.la $(AVROCPP_LIBS) $(BOOST_LOG_LIBS) $(RDKAFKACPP_LIBS) $(LDADD)
