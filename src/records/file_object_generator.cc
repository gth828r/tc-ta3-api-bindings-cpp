// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/file_object_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

FileObjectGenerator::FileObjectGenerator() {}

tc_schema::FileObject
FileObjectGenerator::getRandomFileObject(uint32_t numKvPairs) {
  tc_schema::FileObject fileObj;
  fileObj.uuid = ug.getRandomUuid();
  fileObj.baseObject = aog.getRandomAbstractObject(numKvPairs);
  fileObj.type = this->getRandomFileObjectType();

  fileObj.fileDescriptor = this->getRandomFileDescriptor();
  fileObj.localPrincipal = this->getRandomLocalPrincipal();

  fileObj.size = this->getRandomSize();

  fileObj.peInfo = this->getRandomPeInfo();
  fileObj.hashes = this->getRandomHashes();

  return fileObj;
}

tc_schema::FileObject::size_t
FileObjectGenerator::getRandomSize() {
  tc_schema::FileObject::size_t sz;
  if (oeg.elementIsNull())
    sz.set_null();
  else
    sz.set_long(rand() % 0x0fffffffffffffff);
  return sz;
}

tc_schema::FileObjectType
FileObjectGenerator::getRandomFileObjectType() {
  // FIXME: actually randomize
  return tc_schema::FileObjectType::FILE_OBJECT_FILE;
}

tc_schema::FileObject::fileDescriptor_t
FileObjectGenerator::getRandomFileDescriptor() {
  tc_schema::FileObject::fileDescriptor_t fd;
  if (oeg.elementIsNull())
    fd.set_null();
  else
    fd.set_int((uint32_t) rand() % 0x0fffffff);
  return fd;
}

tc_schema::FileObject::localPrincipal_t
FileObjectGenerator::getRandomLocalPrincipal() {
  tc_schema::FileObject::localPrincipal_t lp;
  if (oeg.elementIsNull())
    lp.set_null();
  else
    lp.set_UUID(ug.getRandomUuid());
  return lp;
}

tc_schema::FileObject::peInfo_t
FileObjectGenerator::getRandomPeInfo() {
  tc_schema::FileObject::peInfo_t pi;
  if (oeg.elementIsNull())
    pi.set_null();
  else
    pi.set_string("RandomPeInfo");
  return pi;
}

tc_schema::FileObject::hashes_t
FileObjectGenerator::getRandomHashes() {
  tc_schema::FileObject::hashes_t hashes;
  if (oeg.elementIsNull())
    hashes.set_null();
  else {
    std::vector<tc_schema::CryptographicHash> v{chg.getRandomCryptographicHash()};
    hashes.set_array(v);
  }
  return hashes;
}

}  // namespace tc_records
