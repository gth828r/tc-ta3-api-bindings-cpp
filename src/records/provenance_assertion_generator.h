// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_PROVENANCE_ASSERTION_GENERATOR_H_
#define TC_RECORDS_PROVENANCE_ASSERTION_GENERATOR_H_

#include "records/optional_element_generator.h"
#include "records/uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class ProvenanceAssertionGenerator {

    static const int32_t MAX_RECURSE = 5;

    OptionalElementGenerator oeg;
    UuidGenerator ug;

    tc_schema::ProvenanceAssertion::sources_t getRandomSources();
    tc_schema::ProvenanceAssertion::provenance_t getRandomProvenance(uint8_t recurse_count);
    tc_schema::ProvenanceAssertion getRandomProvenanceAssertion(uint8_t recurse_count);

  public:
    ProvenanceAssertionGenerator();
    tc_schema::ProvenanceAssertion getRandomProvenanceAssertion();
};

}  // namespace tc_records

#endif  // TC_RECORDS_PROVENANCE_ASSERTION_GENERATOR_H_
