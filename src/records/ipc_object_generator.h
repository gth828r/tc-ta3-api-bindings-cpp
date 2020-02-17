// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_IPC_OBJECT_GENERATOR_H_
#define TC_RECORDS_IPC_OBJECT_GENERATOR_H_

#include "records/abstract_object_generator.h"
#include "records/optional_element_generator.h"
#include "records/uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class IpcObjectGenerator {
 
    AbstractObjectGenerator aog;
    OptionalElementGenerator oeg;
    UuidGenerator ug;

    uint32_t getRandomFileDescriptor();
    tc_schema::IpcObject::fd1_t
      getRandomFD1();
    tc_schema::IpcObject::fd2_t
      getRandomFD2();
    tc_schema::IpcObject::uuid1_t getRandomUUID1();
    tc_schema::IpcObject::uuid2_t getRandomUUID2();

  public:
    IpcObjectGenerator();
    tc_schema::IpcObject getRandomIpcObject(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_IPC_OBJECT_GENERATOR_H_
