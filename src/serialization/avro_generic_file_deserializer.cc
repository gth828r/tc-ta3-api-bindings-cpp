// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "serialization/avro_generic_file_deserializer_impl.h"

#include "avro/Generic.hh"

#include "tc_schema/cdm.h"

namespace tc_serialization {

template class AvroGenericFileDeserializer<tc_schema::TCCDMDatum>;
template class AvroGenericFileDeserializer<avro::GenericDatum>;

}  // namespace tc_serialization
