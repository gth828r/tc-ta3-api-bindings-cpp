// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_CDM_RECORD_PARSER_H
#define TC_CDM_RECORD_PARSER_H

#include "tc_schema/cdm.h"

namespace tc_records {

  class CDMRecordParser {
  public:
    CDMRecordParser();
    bool isTimeMarker(const tc_schema::TCCDMDatum& record);
    tc_schema::TimeMarker getTimeMarker(const tc_schema::TCCDMDatum& record);
    bool isUnitDependency(const tc_schema::TCCDMDatum& record);
    tc_schema::UnitDependency getUnitDependency(const tc_schema::TCCDMDatum& record);
    bool isProvenanceTagNode(const tc_schema::TCCDMDatum& record);
    tc_schema::ProvenanceTagNode getProvenanceTagNode(const tc_schema::TCCDMDatum& record);
    bool isSubject(const tc_schema::TCCDMDatum& record);
    tc_schema::Subject getSubject(const tc_schema::TCCDMDatum& record);
    bool isEvent(const tc_schema::TCCDMDatum& record);
    tc_schema::Event getEvent(const tc_schema::TCCDMDatum& record);
    bool isNetFlowObject(const tc_schema::TCCDMDatum& record);
    tc_schema::NetFlowObject getNetFlowObject(const tc_schema::TCCDMDatum& record);
    bool isFileObject(const tc_schema::TCCDMDatum& record);
    tc_schema::FileObject getFileObject(const tc_schema::TCCDMDatum& record);
    bool isSrcSinkObject(const tc_schema::TCCDMDatum& record);
    tc_schema::SrcSinkObject getSrcSinkObject(const tc_schema::TCCDMDatum& record);
    bool isMemoryObject(const tc_schema::TCCDMDatum& record);
    tc_schema::MemoryObject getMemoryObject(const tc_schema::TCCDMDatum& record);
    bool isPrincipal(const tc_schema::TCCDMDatum& record);
    tc_schema::Principal getPrincipal(const tc_schema::TCCDMDatum& record);
    bool isIpcObject(const tc_schema::TCCDMDatum& record);
    tc_schema::IpcObject getIpcObject(const tc_schema::TCCDMDatum& record);
    bool isRegistryKeyObject(const tc_schema::TCCDMDatum& record);
    tc_schema::RegistryKeyObject getRegistryKeyObject(const tc_schema::TCCDMDatum& record);
    bool isHost(const tc_schema::TCCDMDatum& record);
    tc_schema::Host getHost(const tc_schema::TCCDMDatum& record);
    bool isPacketSocketObject(const tc_schema::TCCDMDatum& record);
    tc_schema::PacketSocketObject getPacketSocketObject(const tc_schema::TCCDMDatum& record);
    bool isEndMarker(const tc_schema::TCCDMDatum& record);
    tc_schema::EndMarker getEndMarker(const tc_schema::TCCDMDatum& record);
    bool isUnknownProvenanceNode(const tc_schema::TCCDMDatum& record);
    tc_schema::UnknownProvenanceNode getUnknownProvenanceNode(const tc_schema::TCCDMDatum& record);
    std::string getType(const tc_schema::TCCDMDatum& record);
  };
}

#endif
