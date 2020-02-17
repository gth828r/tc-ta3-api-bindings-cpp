// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/provenance_tag_node_generator.h"
#include "uuid.h"

namespace tc_records {

ProvenanceTagNodeGenerator::ProvenanceTagNodeGenerator() {}

tc_schema::ProvenanceTagNode
ProvenanceTagNodeGenerator::getRandomProvenanceTagNode(uint32_t numKvPairs) {
  tc_schema::ProvenanceTagNode ptn;

  ptn.tagId = ug.getRandomUuid();
  ptn.subject = ug.getRandomUuid();
  ptn.flowObject = this->getRandomFlowObject();
  ptn.systemCall = this->getRandomSystemCall();
  ptn.programPoint = this->getRandomProgramPoint();
  ptn.prevTagId = this->getRandomPrevTagId();
  ptn.opcode = this->getRandomTagOpCode();
  ptn.tagIds = this->getRandomTagIds();
  ptn.itag = this->getRandomIntegrityTag();
  ptn.ctag = this->getRandomConfidentialityTag();
  ptn.properties = this->getRandomProperties(numKvPairs);
  return ptn;
}

tc_schema::ProvenanceTagNode::tagIds_t
ProvenanceTagNodeGenerator::getRandomTagIds() {
  tc_schema::ProvenanceTagNode::tagIds_t ti;
  if (oeg.elementIsNull())
    ti.set_null();
  else {
    std::vector<boost::array<uint8_t, UUID_LENGTH>> v{ug.getRandomUuid(), ug.getRandomUuid()};
    ti.set_array(v);
  }
  return ti;
}

tc_schema::ProvenanceTagNode::flowObject_t
ProvenanceTagNodeGenerator::getRandomFlowObject() {
  tc_schema::ProvenanceTagNode::flowObject_t fo;
  if (oeg.elementIsNull())
    fo.set_null();
  else
    fo.set_UUID(ug.getRandomUuid());
  return fo;
}

tc_schema::ProvenanceTagNode::prevTagId_t
ProvenanceTagNodeGenerator::getRandomPrevTagId() {
  tc_schema::ProvenanceTagNode::prevTagId_t pti;
  if (oeg.elementIsNull())
    pti.set_null();
  else
    pti.set_UUID(ug.getRandomUuid());
  return pti;
}

tc_schema::ProvenanceTagNode::properties_t
ProvenanceTagNodeGenerator::getRandomProperties(uint32_t numKvPairs) {
  tc_schema::ProvenanceTagNode::properties_t props;
  if (numKvPairs == 0 && oeg.elementIsNull())
    props.set_null();
  else
    props.set_map(pg.getRandomMap(numKvPairs));
  return props;
}

tc_schema::ProvenanceTagNode::systemCall_t
ProvenanceTagNodeGenerator::getRandomSystemCall() {
  tc_schema::ProvenanceTagNode::systemCall_t sc;
  if (oeg.elementIsNull())
    sc.set_null();
  else
    sc.set_string("open");
  return sc;
}


tc_schema::ProvenanceTagNode::programPoint_t
ProvenanceTagNodeGenerator::getRandomProgramPoint() {
  tc_schema::ProvenanceTagNode::programPoint_t pp;
  if (oeg.elementIsNull())
    pp.set_null();
  else
    pp.set_string("MyCode");
  return pp;
}

tc_schema::ProvenanceTagNode::opcode_t
ProvenanceTagNodeGenerator::getRandomTagOpCode() {
  tc_schema::ProvenanceTagNode::opcode_t opcode;
  if (oeg.elementIsNull())
    opcode.set_null();
  else
    opcode.set_TagOpCode(tc_schema::TAG_OP_UNION);
  return opcode;
}

tc_schema::ProvenanceTagNode::itag_t
ProvenanceTagNodeGenerator::getRandomIntegrityTag() {
  tc_schema::ProvenanceTagNode::itag_t itag;
  if (oeg.elementIsNull())
    itag.set_null();
  else
    itag.set_IntegrityTag(tc_schema::INTEGRITY_BENIGN);
  return itag;
}

tc_schema::ProvenanceTagNode::ctag_t
ProvenanceTagNodeGenerator::getRandomConfidentialityTag() {
  tc_schema::ProvenanceTagNode::ctag_t ctag;
  if (oeg.elementIsNull())
    ctag.set_null();
  else
    ctag.set_ConfidentialityTag(tc_schema::CONFIDENTIALITY_SECRET);
  return ctag;
}

}  // namespace tc_records
