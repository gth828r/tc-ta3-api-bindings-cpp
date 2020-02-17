// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_CRYPTOGRAPHIC_HASH_GENERATOR_H_
#define TC_RECORDS_CRYPTOGRAPHIC_HASH_GENERATOR_H_

#include "tc_schema/cdm.h"

namespace tc_records {

class CryptographicHashGenerator {
 
  public:
    CryptographicHashGenerator();
    tc_schema::CryptographicHash getRandomCryptographicHash();
};

}  // namespace tc_records

#endif  // TC_RECORDS_CRYPTOGRAPHIC_HASH_GENERATOR_H_
