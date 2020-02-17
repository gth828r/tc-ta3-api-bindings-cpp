// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/registry_key_object_generator.h"

namespace tc_records {

RegistryKeyObjectGenerator::RegistryKeyObjectGenerator() {}

tc_schema::RegistryKeyObject
RegistryKeyObjectGenerator::getRandomRegistryKeyObject(uint32_t numKvPairs) {
  tc_schema::RegistryKeyObject rkObj;
  rkObj.uuid = ug.getRandomUuid();
  rkObj.baseObject = aog.getRandomAbstractObject(numKvPairs);
  rkObj.key = this->getRandomKey();
  rkObj.value = this->getRandomValue();
  rkObj.size = this->getRandomSize();
  return rkObj;
}

std::string
RegistryKeyObjectGenerator::getRandomKey() {
  // FIXME: actually randomize this
  return "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows";
}

tc_schema::RegistryKeyObject::value_t
RegistryKeyObjectGenerator::getRandomValue() {
  tc_schema::RegistryKeyObject::value_t v;
  if (oeg.elementIsNull())
    v.set_null();
  else
    v.set_Value(vg.getRandomValue());
  return v;
}

tc_schema::RegistryKeyObject::size_t
RegistryKeyObjectGenerator::getRandomSize() {
  tc_schema::RegistryKeyObject::size_t sz;
  if (oeg.elementIsNull())
    sz.set_null();
  else
    sz.set_long(rand() % 0x0fffffffffffffff);
  return sz;
}

}  // namespace tc_records
