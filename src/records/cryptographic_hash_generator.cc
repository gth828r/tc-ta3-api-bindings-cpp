// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/cryptographic_hash_generator.h"

namespace tc_records {

CryptographicHashGenerator::CryptographicHashGenerator() {}

tc_schema::CryptographicHash
CryptographicHashGenerator::getRandomCryptographicHash() {
  tc_schema::CryptographicHash ch;
  ch.type = tc_schema::SHA256;
  ch.hash = "4ad79772ea95d6f5775f293e47bee7f47f08d5b90356490357824893bc097370";
  return ch;
}

}  // namespace tc_records
