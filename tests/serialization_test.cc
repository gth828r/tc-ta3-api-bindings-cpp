// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include <vector>

#include "avro/ValidSchema.hh"

#include "tc_schema/cdm.h"
#include "records/event_generator.h"
#include "records/value_generator.h"
#include "serialization/avro_generic_deserializer.h"
#include "serialization/avro_generic_file_deserializer.h"
#include "serialization/avro_generic_file_serializer.h"
#include "serialization/avro_generic_serializer.h"
#include "serialization/avro_recursion_exception.h"
#include "serialization/utils.h"

#include "gtest/gtest.h"

#define SCHEMA_FILE "TCCDMDatum.avsc"

extern template class tc_serialization::AvroGenericSerializer<tc_schema::TCCDMDatum>;
extern template class tc_serialization::AvroGenericDeserializer<tc_schema::TCCDMDatum>;

class SerializationTest : public ::testing::Test {
  protected:
    avro::ValidSchema writerSchema;
    avro::ValidSchema readerSchema;
    tc_schema::Principal principal;
    tc_schema::Principal::properties_t props;
    tc_schema::TCCDMDatum record;
    std::string expectedJson = std::string(
      "{\"datum\":{\"com.bbn.tc.schema.avro.cdm20.Principal\":"
      "{\"uuid\":\"\\U0000\\U0000\\U0000\\U0000\\U0000\\U0000\\U0000"
      "\\U0000\\U0000\\U0000\\U0000\\U0000\\U0000\\U0000\\U0000\\U0001\","
      "\"type\":\"PRINCIPAL_LOCAL\","
      "\"userId\":\"1002\","
      "\"username\":null,"
      "\"groupIds\":{\"array\":[\"g1\"]},"
      "\"properties\":null}},"
      "\"CDMVersion\":\"20\","
      "\"type\":\"RECORD_HOST\","
      "\"hostId\":\"\\U0000\\U0000\\U0000\\U0000\\U0000\\U0000\\U0000"
      "\\U0000\\U0000\\U0000\\U0000\\U0000\\U0000\\U0000\\U0000\\U0000\","
      "\"sessionNumber\":0,"
      "\"source\":\"SOURCE_LINUX_THEIA\"}"
    );

    SerializationTest() :
      writerSchema(tc_serialization::utils::loadSchema(SCHEMA_FILE)),
      readerSchema(writerSchema) { };

    void SetUp() {
      // Set up the simple edge with some dummy data.
      principal.uuid[15] = 1;
      principal.type = tc_schema::PRINCIPAL_LOCAL;
      principal.userId = "1002";
      std::vector<std::string> v{"g1"};
      principal.groupIds.set_array(v);
      props.set_null();
      principal.properties = props;
      record.datum.set_Principal(principal);
      record.source = tc_schema::SOURCE_LINUX_THEIA;
      record.CDMVersion = "20";
    }
};

TEST_F(SerializationTest, BytesTest) {
  tc_serialization::AvroGenericSerializer<tc_schema::TCCDMDatum> serializer(writerSchema);
  tc_serialization::AvroGenericDeserializer<tc_schema::TCCDMDatum> deserializer(writerSchema, readerSchema);

  // Wrap everything in a try block, since the call to serialize can fail
  try {
    std::vector<uint8_t> binary = serializer.serializeToBytes(record);
    std::unique_ptr<tc_schema::TCCDMDatum> binaryDeserializedRecord =
      deserializer.deserializeBytes(binary);
    std::string jsonString = serializer.serializeToJson(*binaryDeserializedRecord);
    EXPECT_EQ(jsonString, expectedJson);
  } catch (const std::exception &e) {
    FAIL() << e.what();
  } catch (...) {
    FAIL() << "Some unknown exception occurred when serializing the record.";
  }
 
}

TEST_F(SerializationTest, JsonTest) {
  tc_serialization::AvroGenericSerializer<tc_schema::TCCDMDatum> serializer(writerSchema);
  tc_serialization::AvroGenericDeserializer<tc_schema::TCCDMDatum> deserializer(writerSchema, readerSchema);

  // Wrap everything in a try block, since the call to serialize can fail
  try {
    std::string jsonString = serializer.serializeToJson(record);
    EXPECT_EQ(jsonString, expectedJson);
    std::unique_ptr<tc_schema::TCCDMDatum> jsonDeserializedRecord =
      deserializer.deserializeJson(jsonString);
    jsonString = serializer.serializeToJson(*jsonDeserializedRecord);
    EXPECT_EQ(jsonString, expectedJson);
  } catch (const std::exception &e) {
    FAIL() << e.what();
  } catch (...) {
    FAIL() << "Some unknown exception occurred when serializing the record.";
  }
}

TEST_F(SerializationTest, BinaryFileTest) {
  std::string serializationFilename = "out.bin";
  tc_serialization::AvroGenericFileSerializer<tc_schema::TCCDMDatum> fileSerializer(writerSchema, serializationFilename);
  tc_serialization::AvroGenericSerializer<tc_schema::TCCDMDatum> serializer(writerSchema);

  // Wrap everything in a try block, since the call to serialize can fail
  try {
    fileSerializer.serializeToFile(record);
    fileSerializer.close();

    // Don't actually open the file deserializer until records have been written,
    // which can be triggered by closing the file writer.
    tc_serialization::AvroGenericFileDeserializer<tc_schema::TCCDMDatum> fileDeserializer(readerSchema, serializationFilename);
    std::unique_ptr<tc_schema::TCCDMDatum> binaryFileDeserializedRecord =
      fileDeserializer.deserializeNextRecordFromFile();
    std::string jsonString = serializer.serializeToJson(*binaryFileDeserializedRecord);
    EXPECT_EQ(jsonString, expectedJson);
    std::remove("out.bin");
  } catch (const std::exception &e) {
    std::remove("out.bin");
    FAIL() << e.what();
  } catch (...) {
    std::remove("out.bin");
    FAIL() << "Some unknown exception occurred when serializing the record.";
  }
}

TEST_F(SerializationTest, JsonRecursionExceptionTest) {
  tc_serialization::AvroGenericSerializer<tc_schema::TCCDMDatum> serializer(writerSchema);
  tc_schema::TCCDMDatum record;
  tc_records::EventGenerator eg;
  tc_records::ValueGenerator vg;
  tc_schema::Event event = eg.getRandomEvent(1);
  if (event.parameters.is_null()) {
    tc_schema::Event::parameters_t p;
    std::vector<tc_schema::Value> v{vg.getRandomValue()};
    if (v[0].components.is_null()) {
      std::vector<tc_schema::Value> v2{vg.getRandomValue()};
      v[0].components.set_array(v2);
    }
    event.parameters.set_array(v);
  }

  record.datum.set_Event(event);
  EXPECT_NO_THROW(serializer.serializeToJson(record));
}
