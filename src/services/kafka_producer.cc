// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "services/kafka_producer_impl.h"

#include "avro/Generic.hh"
#include "tc_schema/cdm.h"

namespace tc_kafka {

  template class KafkaProducer<tc_schema::TCCDMDatum>;
  template class KafkaProducer<avro::GenericDatum>;

}  // namespace tc_kafka
