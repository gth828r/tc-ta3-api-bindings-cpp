// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_FILE_OBJECT_GENERATOR_H_
#define TC_RECORDS_FILE_OBJECT_GENERATOR_H_

#include "records/cryptographic_hash_generator.h"
#include "records/abstract_object_generator.h"
#include "records/optional_element_generator.h"
#include "records/uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class FileObjectGenerator {
    CryptographicHashGenerator chg;
    OptionalElementGenerator oeg;
    AbstractObjectGenerator aog;
    UuidGenerator ug;
    tc_schema::FileObjectType type;

    tc_schema::FileObject::size_t getRandomSize();
    tc_schema::FileObject::fileDescriptor_t getRandomFileDescriptor();
    tc_schema::FileObject::localPrincipal_t getRandomLocalPrincipal();
    tc_schema::FileObject::peInfo_t getRandomPeInfo();
    tc_schema::FileObject::hashes_t getRandomHashes();
    tc_schema::FileObjectType getRandomFileObjectType();

  public:
    FileObjectGenerator();
    tc_schema::FileObject getRandomFileObject(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_FILE_OBJECT_GENERATOR_H_
