// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/unknown_provenance_node_generator.h"

namespace tc_records {

UnknownProvenanceNodeGenerator::UnknownProvenanceNodeGenerator() {}

tc_schema::UnknownProvenanceNode
UnknownProvenanceNodeGenerator::getRandomUnknownProvenanceNode(uint32_t numKvPairs) {
  tc_schema::UnknownProvenanceNode upn;

  upn.upnTagId = ug.getRandomUuid();

  if (oeg.elementIsNull())
    upn.subject.set_null();
  else
    upn.subject.set_UUID(ug.getRandomUuid());

  if (oeg.elementIsNull())
    upn.programPoint.set_null();
  else
    upn.programPoint.set_string("CppProgramPoint");

  upn.properties = this->getRandomProperties(numKvPairs);

  return upn;
}

tc_schema::UnknownProvenanceNode::properties_t
UnknownProvenanceNodeGenerator::getRandomProperties(uint32_t numKvPairs) {
  tc_schema::UnknownProvenanceNode::properties_t props;
  if (numKvPairs == 0 && oeg.elementIsNull())
    props.set_null();
  else
    props.set_map(pg.getRandomMap(numKvPairs));
  return props;
}

}  // namespace tc_records
