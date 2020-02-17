# Copyright (c) 2020 Raytheon BBN Technologies Corp.
# See LICENSE.txt for details.

serializationdir=$(pkgincludedir)/serialization

AM_CXXFLAGS = -I$(srcdir)/.. $(CONFIGURE_CXXFLAGS)

# Headers
serialization_HEADERS = avro_generic_deserializer.h \
                        avro_generic_deserializer_fwd.h \
                        avro_generic_deserializer_impl.h \
                        avro_generic_file_deserializer.h \
                        avro_generic_file_deserializer_fwd.h \
                        avro_generic_file_deserializer_impl.h \
                        avro_generic_file_serializer.h \
                        avro_generic_file_serializer_fwd.h \
                        avro_generic_file_serializer_impl.h \
                        avro_generic_serializer.h \
                        avro_generic_serializer_fwd.h \
                        avro_generic_serializer_impl.h \
                        avro_recursion_exception.h \
                        utils.h

noinst_LTLIBRARIES = libserialization.la
libserialization_la_SOURCES = avro_generic_deserializer.cc \
                              avro_generic_file_deserializer.cc \
                              avro_generic_file_serializer.cc \
                              avro_generic_serializer.cc \
                              utils.cc
