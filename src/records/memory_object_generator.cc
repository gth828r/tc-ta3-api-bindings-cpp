// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/memory_object_generator.h"

namespace tc_records {

MemoryObjectGenerator::MemoryObjectGenerator() {}

tc_schema::MemoryObject
MemoryObjectGenerator::getRandomMemoryObject(uint32_t numKvPairs) {
  tc_schema::MemoryObject mObj;
  mObj.uuid = ug.getRandomUuid();
  mObj.baseObject = aog.getRandomAbstractObject(numKvPairs);
  mObj.memoryAddress = this->getRandomMemoryAddress();
  mObj.pageOffset = this->getRandomPageOffset();
  mObj.pageNumber = this->getRandomPageNumber();
  mObj.size = this->getRandomSize();
  return mObj;
}

int64_t
MemoryObjectGenerator::getRandomMemoryAddress() {
  return rand() % 0x0fffffffffffffff;
}

tc_schema::MemoryObject::pageOffset_t
MemoryObjectGenerator::getRandomPageOffset() {
  tc_schema::MemoryObject::pageOffset_t po;
  if (oeg.elementIsNull())
    po.set_null();
  else
    po.set_long(rand() % 0x0fffffffffffffff);
  return po;
}

tc_schema::MemoryObject::pageNumber_t
MemoryObjectGenerator::getRandomPageNumber() {
  tc_schema::MemoryObject::pageNumber_t pg;
  if (oeg.elementIsNull())
    pg.set_null();
  else
    pg.set_long(rand() % 0x0fffffffffffffff);
  return pg;
}

tc_schema::MemoryObject::size_t
MemoryObjectGenerator::getRandomSize() {
  tc_schema::MemoryObject::size_t sz;
  if (oeg.elementIsNull())
    sz.set_null();
  else
    sz.set_long(rand() % 0x0fffffffffffffff);
  return sz;
}

}  // namespace tc_records
