// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/abstract_object_generator.h"

namespace tc_records {

AbstractObjectGenerator::AbstractObjectGenerator() {}

tc_schema::AbstractObject
AbstractObjectGenerator::getRandomAbstractObject(uint32_t numKvPairs) {
  tc_schema::AbstractObject obj;
  obj.permission = this->getRandomPermission();
  obj.epoch = this->getRandomEpoch();
  obj.properties = this->getRandomProperties(numKvPairs);
  return obj;
}

tc_schema::AbstractObject::permission_t
AbstractObjectGenerator::getRandomPermission() {
  tc_schema::AbstractObject::permission_t perm;
  if (oeg.elementIsNull()) {
    perm.set_null();
  } else {
    boost::array<uint8_t, 2>v = {(uint8_t) (rand()%256),
                                 (uint8_t) (rand()%256)};
    perm.set_SHORT(v);
  }
  return perm;
}

tc_schema::AbstractObject::epoch_t
AbstractObjectGenerator::getRandomEpoch() {
  tc_schema::AbstractObject::epoch_t epoch;
  if (oeg.elementIsNull())
    epoch.set_null();
  else
    epoch.set_int((uint32_t) (rand() % 0x0fffffff));
  return epoch;
}

tc_schema::AbstractObject::properties_t
AbstractObjectGenerator::getRandomProperties(uint32_t numKvPairs) {
  tc_schema::AbstractObject::properties_t props;
  if (numKvPairs == 0 && oeg.elementIsNull()) {
    props.set_null();
  } else {
    props.set_map(pg.getRandomMap(numKvPairs));
  }
  return props;
}

}  // namespace tc_records
