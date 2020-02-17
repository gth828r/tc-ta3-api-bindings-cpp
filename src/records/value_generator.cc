// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/value_generator.h"

namespace tc_records {

ValueGenerator::ValueGenerator() { }

tc_schema::Value
ValueGenerator::getRandomValue() {
  tc_schema::Value value;
  value.size = this->getRandomSize();
  value.type = this->getRandomType();
  value.valueDataType = this->getRandomValueDataType();
  value.isNull = this->getRandomIsNull();
  value.name = this->getRandomName();
  value.runtimeDataType = this->getRandomRuntimeDataType();
  value.valueBytes = this->getRandomValueBytes();
  value.tag = this->getRandomTag();
  value.components = this->getRandomComponents();

  if (oeg.elementIsNull())
    value.provenance.set_null();
  else {
    std::vector<tc_schema::ProvenanceAssertion> v{pag.getRandomProvenanceAssertion()};
    value.provenance.set_array(v);
  }

  return value;
}

int32_t
ValueGenerator::getRandomSize() {
  return rand() % 0x0fffffff;
}

tc_schema::ValueType
ValueGenerator::getRandomType() {
  // FIXME: actually randomize this
  return tc_schema::VALUE_TYPE_CONTROL;
}

tc_schema::ValueDataType
ValueGenerator::getRandomValueDataType() {
  // FIXME: actually randomize this
  return tc_schema::VALUE_DATA_TYPE_BYTE;
}

bool
ValueGenerator::getRandomIsNull() {
  return (rand() % 2 > 0);
}

tc_schema::Value::name_t
ValueGenerator::getRandomName() {
  tc_schema::Value::name_t name;
  if (oeg.elementIsNull())
    name.set_null();
  else
    // FIXME: actually randomize this
    name.set_string("PrettayPrettayPrettyGood");
  return name;
}

tc_schema::Value::runtimeDataType_t
ValueGenerator::getRandomRuntimeDataType() {
  tc_schema::Value::runtimeDataType_t rdt;
  if (oeg.elementIsNull())
    rdt.set_null();
  else
    // FIXME: actually randomize this
    rdt.set_string("MyCustomByteBuffer");
  return rdt;
}

tc_schema::Value::valueBytes_t
ValueGenerator::getRandomValueBytes() {
  tc_schema::Value::valueBytes_t vbt;
  if (oeg.elementIsNull())
    vbt.set_null();
  else {
    // FIXME: actually randomize this
    std::vector<uint8_t> v {1, 2, 3};
    vbt.set_bytes(v);
  }
  return vbt;
}

tc_schema::Value::tag_t
ValueGenerator::getRandomTag() {
  tc_schema::Value::tag_t tag;
  if (oeg.elementIsNull())
    tag.set_null();
  else {
    std::vector<tc_schema::TagRunLengthTuple> v{trltg.getRandomTagRunLengthTuple()};
    tag.set_array(v);
  }
  return tag;
}

tc_schema::Value::components_t
ValueGenerator::getRandomComponents() {
  // FIXME: to avoid infinite recursion, always set this to null for now.
  tc_schema::Value::components_t components;
  if (oeg.elementIsNull())
    components.set_null();
  else {
    std::vector<tc_schema::Value> v{this->getRandomValue()};
    components.set_array(v);
  }
  return components;
}

}  // namespace tc_records
