// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "avro/ValidSchema.hh"

#include "records/cdm_record_generator.h"
#include "serialization/avro_generic_deserializer.h"
#include "serialization/avro_generic_file_deserializer.h"
#include "serialization/avro_generic_file_serializer.h"
#include "serialization/avro_generic_serializer.h"
#include "serialization/avro_recursion_exception.h"
#include "serialization/utils.h"
#include "tc_schema/cdm.h"

#include "gtest/gtest.h"

#define SCHEMA_FILE "TCCDMDatum.avsc"

extern template class tc_serialization::AvroGenericSerializer<tc_schema::TCCDMDatum>;

class RecordGeneratorTest : public ::testing::Test {
  protected:
    uint32_t numKvPairs;
    tc_records::CDMRecordGenerator gen;

    RecordGeneratorTest() : numKvPairs(5) { };
};

void doTest(tc_schema::TCCDMDatum record) {
  tc_serialization::AvroGenericSerializer<tc_schema::TCCDMDatum> serializer(SCHEMA_FILE);
  // This should raise an exception if the record is invalid.
  try {
    serializer.serializeToBytes(record);
  } catch (const std::exception &e) {
    FAIL() << e.what();
  } catch (...) {
    FAIL() << "Some unknown exception occurred when serializing the record.";
  }
}

TEST_F(RecordGeneratorTest, ProvenanceTagNodeTest) {
  SCOPED_TRACE("ProvenanceTagNode");
  doTest(gen.getRandomProvenanceTagNodeRecord(numKvPairs));
}

TEST_F(RecordGeneratorTest, SubjectTest) {
  SCOPED_TRACE("Subject");
  doTest(gen.getRandomSubjectRecord(numKvPairs));
}

TEST_F(RecordGeneratorTest, EventTest) {
  SCOPED_TRACE("Event");
  doTest(gen.getRandomEventRecord(numKvPairs));
}

TEST_F(RecordGeneratorTest, NetFlowObjectTest) {
  SCOPED_TRACE("NetFlowObject");
  doTest(gen.getRandomNetFlowObjectRecord(numKvPairs));
}

TEST_F(RecordGeneratorTest, FileObjectTest) {
  SCOPED_TRACE("FileObject");
  doTest(gen.getRandomFileObjectRecord(numKvPairs));
}

TEST_F(RecordGeneratorTest, MemoryObjectTest) {
  SCOPED_TRACE("MemoryObject");
  doTest(gen.getRandomMemoryObjectRecord(numKvPairs));
}

TEST_F(RecordGeneratorTest, SrcSinkObjectTest) {
  SCOPED_TRACE("SrcSinkObject");
  doTest(gen.getRandomSrcSinkObjectRecord(numKvPairs));
}

TEST_F(RecordGeneratorTest, PrincipalTest) {
  SCOPED_TRACE("Principle");
  doTest(gen.getRandomPrincipalRecord(numKvPairs));
}

TEST_F(RecordGeneratorTest, IpcObjectTest) {
  SCOPED_TRACE("IpcPipeObject");
  doTest(gen.getRandomIpcObjectRecord(numKvPairs));
}

TEST_F(RecordGeneratorTest, UnitDependencyTest) {
  SCOPED_TRACE("UnitDependency");
  doTest(gen.getRandomUnitDependencyRecord());
}

TEST_F(RecordGeneratorTest, TimeMarkerTest) {
  SCOPED_TRACE("TimeMarker");
  doTest(gen.getRandomTimeMarkerRecord());
}

TEST_F(RecordGeneratorTest, RegistryKeyObjectTest) {
  SCOPED_TRACE("RegistryKeyObject");
  doTest(gen.getRandomRegistryKeyObjectRecord(numKvPairs));
}

TEST_F(RecordGeneratorTest, PacketSocketObjectTest) {
  SCOPED_TRACE("PacketSocketObject");
  doTest(gen.getRandomPacketSocketObjectRecord(numKvPairs));
}

TEST_F(RecordGeneratorTest, HostTest) {
  SCOPED_TRACE("Host");
  doTest(gen.getRandomHostRecord());
}

TEST_F(RecordGeneratorTest, EndMarkerTest) {
  SCOPED_TRACE("EndMarker");
  doTest(gen.getRandomEndMarkerRecord());
}

TEST_F(RecordGeneratorTest, UnknownProvenanceNodeTest) {
  SCOPED_TRACE("UnknownProvenanceNode");
  doTest(gen.getRandomUnknownProvenanceNodeRecord(numKvPairs));
}

TEST_F(RecordGeneratorTest, RandomRecordsTest) {
  SCOPED_TRACE("Random");
  for (uint32_t i = 0; i < 32; i++) {
    doTest(gen.getRandomRecord(numKvPairs));
  }
}
