# Copyright (c) 2020 Raytheon BBN Technologies Corp.
# See LICENSE.txt for details.

recordsdir=$(pkgincludedir)/records

AM_CXXFLAGS = -I$(srcdir)/.. $(CONFIGURE_CXXFLAGS)

# Headers
records_HEADERS = abstract_object_generator.h \
                  cdm_record_generator.h \
                  event_generator.h \
                  file_object_generator.h \
                  instrumentation_source_generator.h \
                  measurable_cdm_record_generator.h \
                  memory_object_generator.h \
                  net_flow_object_generator.h \
                  principal_generator.h \
                  property_generator.h \
                  provenance_tag_node_generator.h \
                  optional_element_generator.h \
                  registry_key_object_generator.h \
                  src_sink_object_generator.h \
                  subject_generator.h \
                  timestamp_generator.h \
                  uuid.h \
                  uuid_generator.h \
                  value_generator.h \
                  tag_run_length_tuple_generator.h \
                  cryptographic_hash_generator.h \
                  ipc_object_generator.h \
                  time_marker_generator.h \
                  unit_dependency_generator.h \
                  end_marker_generator.h \
                  host_identifier_generator.h \
                  interface_generator.h \
                  host_generator.h \
                  provenance_assertion_generator.h \
                  packet_socket_object_generator.h \
                  unknown_provenance_node_generator.h \
		  cdm_record_parser.h

noinst_LTLIBRARIES = librecords.la
librecords_la_SOURCES = abstract_object_generator.cc \
                        cdm_record_generator.cc \
                        event_generator.cc \
                        file_object_generator.cc \
                        measurable_cdm_record_generator.cc \
                        memory_object_generator.cc \
                        net_flow_object_generator.cc \
                        principal_generator.cc \
                        provenance_tag_node_generator.cc \
                        registry_key_object_generator.cc \
                        src_sink_object_generator.cc \
                        subject_generator.cc \
                        tag_run_length_tuple_generator.cc \
                        cryptographic_hash_generator.cc \
                        ipc_object_generator.cc \
                        time_marker_generator.cc \
                        unit_dependency_generator.cc \
                        value_generator.cc \
                        end_marker_generator.cc \
                        host_identifier_generator.cc \
                        interface_generator.cc \
                        host_generator.cc \
                        provenance_assertion_generator.cc \
                        packet_socket_object_generator.cc \
                        unknown_provenance_node_generator.cc \
			cdm_record_parser.cc
