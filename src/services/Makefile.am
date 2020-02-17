# Copyright (c) 2020 Raytheon BBN Technologies Corp.
# See LICENSE.txt for details.

servicesdir=$(pkgincludedir)/services

AM_CXXFLAGS = -I$(srcdir)/.. $(CONFIGURE_CXXFLAGS) -DBOOST_LOG_DYN_LINK

# Headers
services_HEADERS = kafka_client.h \
                   kafka_callbacks.h \
		   kafka_producer.h \
		   kafka_producer_impl.h \
		   kafka_consumer.h \
		   kafka_consumer_impl.h

noinst_LTLIBRARIES = libservices.la
libservices_la_SOURCES = kafka_client.cc \
		         kafka_callbacks.cc \
                         kafka_producer.cc \
                         kafka_consumer.cc
