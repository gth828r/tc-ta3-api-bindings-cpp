// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "serialization/avro_generic_file_serializer_impl.h"

#include "avro/Generic.hh"

#include "tc_schema/cdm.h"

namespace tc_serialization {

template class AvroGenericFileSerializer<tc_schema::TCCDMDatum>;
template class AvroGenericFileSerializer<avro::GenericDatum>;

}  // namespace tc_serialization
