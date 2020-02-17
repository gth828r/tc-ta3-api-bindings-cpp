// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_UNKNOWN_PROVENANCE_NODE_GENERATOR_H_
#define TC_RECORDS_UNKNOWN_PROVENANCE_NODE_GENERATOR_H_

#include "records/property_generator.h"
#include "records/optional_element_generator.h"
#include "records/uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class UnknownProvenanceNodeGenerator {

    PropertyGenerator pg;
    OptionalElementGenerator oeg;
    UuidGenerator ug;

    tc_schema::UnknownProvenanceNode::properties_t getRandomProperties(uint32_t numKvPairs);

  public:
    UnknownProvenanceNodeGenerator();
    tc_schema::UnknownProvenanceNode getRandomUnknownProvenanceNode(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_UNKNOWN_PROVENANCE_NODE_GENERATOR_H_
