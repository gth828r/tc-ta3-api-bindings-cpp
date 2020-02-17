// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/ipc_object_generator.h"

namespace tc_records {

IpcObjectGenerator::IpcObjectGenerator() {}

tc_schema::IpcObject
IpcObjectGenerator::getRandomIpcObject(uint32_t numKvPairs) {
  tc_schema::IpcObject ipcObj;
  ipcObj.uuid = ug.getRandomUuid();
  ipcObj.baseObject = aog.getRandomAbstractObject(numKvPairs);
  ipcObj.type = tc_schema::IPC_OBJECT_PIPE_UNNAMED;

  switch (oeg.anyIndex(2)) {
  case 0:
    ipcObj.fd1 = this->getRandomFD1();
    ipcObj.fd2 = this->getRandomFD2();
    ipcObj.uuid1.set_null();
    ipcObj.uuid2.set_null();

  case 1:
    ipcObj.fd1.set_null();
    ipcObj.fd2.set_null();
    ipcObj.uuid1 = this->getRandomUUID1();
    ipcObj.uuid2 = this->getRandomUUID2();
  }

  return ipcObj;
}

tc_schema::IpcObject::fd1_t
IpcObjectGenerator::getRandomFD1() {
  tc_schema::IpcObject::fd1_t sfd;
  sfd.set_int(this->getRandomFileDescriptor());
  return sfd;
}

tc_schema::IpcObject::fd2_t
IpcObjectGenerator::getRandomFD2() {
  tc_schema::IpcObject::fd2_t sfd;
  sfd.set_int(this->getRandomFileDescriptor());
  return sfd;
}

tc_schema::IpcObject::uuid1_t
IpcObjectGenerator::getRandomUUID1() {
  tc_schema::IpcObject::uuid1_t uuid;
  uuid.set_UUID(ug.getRandomUuid());
  return uuid;
}

tc_schema::IpcObject::uuid2_t
IpcObjectGenerator::getRandomUUID2() {
  tc_schema::IpcObject::uuid2_t uuid;
  uuid.set_UUID(ug.getRandomUuid());
  return uuid;
}

uint32_t
IpcObjectGenerator::getRandomFileDescriptor() {
  // FIXME: actually randomize this
  return (uint32_t) rand() % 0x0fffffff;
}

}  // namespace tc_records
