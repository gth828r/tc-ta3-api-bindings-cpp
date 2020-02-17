// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_PROVENANCE_TAG_NODE_GENERATOR_H_
#define TC_RECORDS_PROVENANCE_TAG_NODE_GENERATOR_H_

#include "records/optional_element_generator.h"
#include "records/property_generator.h"
#include "records/uuid_generator.h"
#include "records/value_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class ProvenanceTagNodeGenerator {

    OptionalElementGenerator oeg;
    PropertyGenerator pg;
    UuidGenerator ug;

    tc_schema::ProvenanceTagNode::properties_t getRandomProperties(uint32_t numKvPairs);
    tc_schema::ProvenanceTagNode::flowObject_t getRandomFlowObject();
    tc_schema::ProvenanceTagNode::systemCall_t getRandomSystemCall();
    tc_schema::ProvenanceTagNode::programPoint_t getRandomProgramPoint();
    tc_schema::ProvenanceTagNode::opcode_t getRandomTagOpCode();
    tc_schema::ProvenanceTagNode::itag_t getRandomIntegrityTag();
    tc_schema::ProvenanceTagNode::ctag_t getRandomConfidentialityTag();
    tc_schema::ProvenanceTagNode::prevTagId_t getRandomPrevTagId();
    tc_schema::ProvenanceTagNode::tagIds_t getRandomTagIds();

  public:
    ProvenanceTagNodeGenerator();
    tc_schema::ProvenanceTagNode getRandomProvenanceTagNode(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_PROVENANCE_TAG_NODE_GENERATOR_H_
