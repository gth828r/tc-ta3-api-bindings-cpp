// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/provenance_assertion_generator.h"

namespace tc_records {

ProvenanceAssertionGenerator::ProvenanceAssertionGenerator() {}

tc_schema::ProvenanceAssertion
ProvenanceAssertionGenerator::getRandomProvenanceAssertion() {
  return this->getRandomProvenanceAssertion(0);
}


tc_schema::ProvenanceAssertion
ProvenanceAssertionGenerator::getRandomProvenanceAssertion(uint8_t recurse_count) {
  tc_schema::ProvenanceAssertion pa;

  pa.asserter = ug.getRandomUuid();
  pa.sources = this->getRandomSources();
  pa.provenance = this->getRandomProvenance(recurse_count);

  return pa;
}

tc_schema::ProvenanceAssertion::provenance_t
ProvenanceAssertionGenerator::getRandomProvenance(uint8_t recurse_count) {
  tc_schema::ProvenanceAssertion::provenance_t p;

  if (oeg.elementIsNull())
    p.set_null();
  else {
    if (recurse_count >= ProvenanceAssertionGenerator::MAX_RECURSE)
      p.set_null();
    else {
      std::vector<tc_schema::ProvenanceAssertion> v{this->getRandomProvenanceAssertion(recurse_count + 1)};
      p.set_array(v);
    }
  }

  return p;
}

tc_schema::ProvenanceAssertion::sources_t
ProvenanceAssertionGenerator::getRandomSources() {
  tc_schema::ProvenanceAssertion::sources_t s;
  if (oeg.elementIsNull())
    s.set_null();
  else {
    std::vector<boost::array<uint8_t, UUID_LENGTH>> v{ug.getRandomUuid(), ug.getRandomUuid()};
    s.set_array(v);
  }
  return s;
}

}  // namespace tc_records
