// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/cdm_record_generator.h"

#include <ctime>
#include <cstdlib>

namespace tc_records {

const std::string CDMRecordGenerator::CDM_VERSION = "20";
const uint32_t CDMRecordGenerator::NUM_DATA_TYPES = 16;
const uint32_t CDMRecordGenerator::SESSION_NUM = 1;

CDMRecordGenerator::CDMRecordGenerator() {
  srand(time(NULL));
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomRecord(uint32_t numKvPairs) {
  uint32_t val = rand() % CDMRecordGenerator::NUM_DATA_TYPES;

  switch (val) {
  case 0:
    return this->getRandomHostRecord();
    break;

  case 1:
    return this->getRandomPrincipalRecord(numKvPairs);
    break;

  case 2:
    return this->getRandomProvenanceTagNodeRecord(numKvPairs);
    break;

  case 3:
    return this->getRandomSubjectRecord(numKvPairs);
    break;

  case 4:
    return this->getRandomFileObjectRecord(numKvPairs);
    break;

  case 5:
    return this->getRandomIpcObjectRecord(numKvPairs);
    break;

  case 6:
    return this->getRandomRegistryKeyObjectRecord(numKvPairs);
    break;

  case 7:
    return this->getRandomPacketSocketObjectRecord(numKvPairs);
    break;

  case 8:
    return this->getRandomNetFlowObjectRecord(numKvPairs);
    break;

  case 9:
    return this->getRandomMemoryObjectRecord(numKvPairs);
    break;

  case 10:
    return this->getRandomSrcSinkObjectRecord(numKvPairs);
    break;

  case 11:
    return this->getRandomEventRecord(numKvPairs);
    break;

  case 12:
    return this->getRandomUnitDependencyRecord();
    break;

  case 13:
    return this->getRandomTimeMarkerRecord();
    break;

  case 14:
    return this->getRandomEndMarkerRecord();
    break;

  case 15:
    return this->getRandomUnknownProvenanceNodeRecord(numKvPairs);
    break;

  default:
    // Raise exception... need to implement a generator for a new type!
    throw std::out_of_range("Randomly generated int " + std::to_string(val) +
      " does not map to a data generator type");
  }
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomProvenanceTagNodeRecord(uint32_t numKvPairs) {
  tc_schema::TCCDMDatum record;
  record.datum.set_ProvenanceTagNode(
    ptng.getRandomProvenanceTagNode(numKvPairs));
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_PROVENANCE_TAG_NODE;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomSubjectRecord(uint32_t numKvPairs) {
  tc_schema::TCCDMDatum record;
  record.datum.set_Subject(sg.getRandomSubject(numKvPairs));
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_SUBJECT;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomEventRecord(uint32_t numKvPairs) {
  tc_schema::TCCDMDatum record;
  record.datum.set_Event(eg.getRandomEvent(numKvPairs));
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_EVENT;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomNetFlowObjectRecord(uint32_t numKvPairs) {
  tc_schema::TCCDMDatum record;
  record.datum.set_NetFlowObject(nfog.getRandomNetFlowObject(numKvPairs));
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_NET_FLOW_OBJECT;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomFileObjectRecord(uint32_t numKvPairs) {
  tc_schema::TCCDMDatum record;
  record.datum.set_FileObject(fog.getRandomFileObject(numKvPairs));
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_FILE_OBJECT;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomSrcSinkObjectRecord(uint32_t numKvPairs) {
  tc_schema::TCCDMDatum record;
  record.datum.set_SrcSinkObject(ssog.getRandomSrcSinkObject(numKvPairs));
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_SRC_SINK_OBJECT;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomMemoryObjectRecord(uint32_t numKvPairs) {
  tc_schema::TCCDMDatum record;
  record.datum.set_MemoryObject(mog.getRandomMemoryObject(numKvPairs));
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_MEMORY_OBJECT;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomPrincipalRecord(uint32_t numKvPairs) {
  tc_schema::TCCDMDatum record;
  record.datum.set_Principal(pg.getRandomPrincipal(numKvPairs));
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_PRINCIPAL;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomTimeMarkerRecord() {
  tc_schema::TCCDMDatum record;
  record.datum.set_TimeMarker(tmg.getRandomTimeMarker());
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_TIME_MARKER;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomUnitDependencyRecord() {
  tc_schema::TCCDMDatum record;
  record.datum.set_UnitDependency(udg.getRandomUnitDependency());
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_UNIT_DEPENDENCY;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomIpcObjectRecord(uint32_t numKvPairs) {
  tc_schema::TCCDMDatum record;
  record.datum.set_IpcObject(iog.getRandomIpcObject(numKvPairs));
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_IPC_OBJECT;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomRegistryKeyObjectRecord(uint32_t numKvPairs) {
  tc_schema::TCCDMDatum record;
  record.datum.set_RegistryKeyObject(rkog.getRandomRegistryKeyObject(numKvPairs));
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_REGISTRY_KEY_OBJECT;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomHostRecord() {
  tc_schema::TCCDMDatum record;
  record.datum.set_Host(hg.getRandomHost());
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_HOST;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomPacketSocketObjectRecord(uint32_t numKvPairs) {
  tc_schema::TCCDMDatum record;
  record.datum.set_PacketSocketObject(psog.getRandomPacketSocketObject(numKvPairs));
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_PACKET_SOCKET_OBJECT;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomEndMarkerRecord() {
  tc_schema::TCCDMDatum record;
  record.datum.set_EndMarker(emg.getRandomEndMarker());
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid(); 
  record.type = tc_schema::RECORD_END_MARKER;
  return record;
}

tc_schema::TCCDMDatum
CDMRecordGenerator::getRandomUnknownProvenanceNodeRecord(uint32_t numKvPairs) {
  tc_schema::TCCDMDatum record;
  record.datum.set_UnknownProvenanceNode(upng.getRandomUnknownProvenanceNode(numKvPairs));
  record.source = isg.getRandomSource();
  record.CDMVersion = CDMRecordGenerator::CDM_VERSION;
  record.sessionNumber = CDMRecordGenerator::SESSION_NUM;
  record.hostId = ug.getRandomUuid();
  record.type = tc_schema::RECORD_END_MARKER;
  return record;
}


}  // namespace tc_records
