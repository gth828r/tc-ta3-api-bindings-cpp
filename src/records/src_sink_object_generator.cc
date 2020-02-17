// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/src_sink_object_generator.h"

namespace tc_records {

SrcSinkObjectGenerator::SrcSinkObjectGenerator() {}

tc_schema::SrcSinkObject
SrcSinkObjectGenerator::getRandomSrcSinkObject(uint32_t numKvPairs) {
  tc_schema::SrcSinkObject ssObj;
  ssObj.uuid = ug.getRandomUuid();
  ssObj.baseObject = aog.getRandomAbstractObject(numKvPairs);
  ssObj.type = this->getRandomType();
  ssObj.fileDescriptor = this->getRandomFileDescriptor();
  return ssObj;
}

tc_schema::SrcSinkType
SrcSinkObjectGenerator::getRandomType() {
  // FIXME: actually randomize this
  return tc_schema::SRCSINK_ENV_VARIABLE;
}

tc_schema::SrcSinkObject::fileDescriptor_t
SrcSinkObjectGenerator::getRandomFileDescriptor() {
  tc_schema::SrcSinkObject::fileDescriptor_t fd;
  if (oeg.elementIsNull())
    fd.set_null();
  else
    fd.set_int(rand() % 0xffff);
  return fd;
}

}  // namespace tc_records
