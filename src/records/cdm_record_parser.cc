// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "cdm_record_parser.h"

namespace tc_records {

  CDMRecordParser::CDMRecordParser() {
  }

  bool CDMRecordParser::isTimeMarker(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 14) {
      return true;
    }
    return false;
  }

  tc_schema::TimeMarker CDMRecordParser::getTimeMarker(const tc_schema::TCCDMDatum& record) {
    if (isTimeMarker(record)) {
      return record.datum.get_TimeMarker();
    } else {
      throw std::invalid_argument("Record is not of type TimeMarker.");
    }
  }

  bool CDMRecordParser::isUnitDependency(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 13) {
      return true;
    }
    return false;
  }

  tc_schema::UnitDependency CDMRecordParser::getUnitDependency(const tc_schema::TCCDMDatum& record) {
    if (isUnitDependency(record)) {
      return record.datum.get_UnitDependency();
    } else {
      throw std::invalid_argument("Record is not of type UnitDependency.");
    }
  }

  bool CDMRecordParser::isProvenanceTagNode(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 2) {
      return true;
    }
    return false;
  }

  tc_schema::ProvenanceTagNode CDMRecordParser::getProvenanceTagNode(const tc_schema::TCCDMDatum& record) {
    if (isProvenanceTagNode(record)) {
      return record.datum.get_ProvenanceTagNode();
    } else {
      throw std::invalid_argument("Record is not of type ProvenanceTagNode.");
    }
  }

  bool CDMRecordParser::isUnknownProvenanceNode(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 3) {
      return true;
    }
    return false;
  }

  tc_schema::UnknownProvenanceNode CDMRecordParser::getUnknownProvenanceNode(const tc_schema::TCCDMDatum& record) {
    if (isUnknownProvenanceNode(record)) {
      return record.datum.get_UnknownProvenanceNode();
    } else {
      throw std::invalid_argument("Record is not of type UnknownProvenanceNode.");
    }
  }

  bool CDMRecordParser::isSubject(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 4) {
      return true;
    }
    return false;
  }

  tc_schema::Subject CDMRecordParser::getSubject(const tc_schema::TCCDMDatum& record) {
    if (isSubject(record)) {
      return record.datum.get_Subject();
    } else {
      throw std::invalid_argument("Record is not of type Subject.");
    }
  }

  bool CDMRecordParser::isEvent(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 12) {
      return true;
    }
    return false;
  }

  tc_schema::Event CDMRecordParser::getEvent(const tc_schema::TCCDMDatum& record) {
    if (isEvent(record)) {
      return record.datum.get_Event();
    } else {
      throw std::invalid_argument("Record is not of type Event.");
    }
  }

  bool CDMRecordParser::isNetFlowObject(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 9) {
      return true;
    }
    return false;
  }

  tc_schema::NetFlowObject CDMRecordParser::getNetFlowObject(const tc_schema::TCCDMDatum& record) {
    if (isNetFlowObject(record)) {
      return record.datum.get_NetFlowObject();
    } else {
      throw std::invalid_argument("Record is not of type NetFlowObject.");
    }
  }

  bool CDMRecordParser::isFileObject(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 5) {
      return true;
    }
    return false;
  }

  tc_schema::FileObject CDMRecordParser::getFileObject(const tc_schema::TCCDMDatum& record) {
    if (isFileObject(record)) {
      return record.datum.get_FileObject();
    } else {
      throw std::invalid_argument("Record is not of type FileObject.");
    }
  }

  bool CDMRecordParser::isSrcSinkObject(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 11) {
      return true;
    }
    return false;
  }

  tc_schema::SrcSinkObject CDMRecordParser::getSrcSinkObject(const tc_schema::TCCDMDatum& record) {
    if (isSrcSinkObject(record)) {
      return record.datum.get_SrcSinkObject();
    } else {
      throw std::invalid_argument("Record is not of type SrcSinkObject.");
    }
  }

  bool CDMRecordParser::isMemoryObject(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 10) {
      return true;
    }
    return false;
  }

  tc_schema::MemoryObject CDMRecordParser::getMemoryObject(const tc_schema::TCCDMDatum& record) {
    if (isMemoryObject(record)) {
      return record.datum.get_MemoryObject();
    } else {
      throw std::invalid_argument("Record is not of type MemoryObject.");
    }
  }

  bool CDMRecordParser::isPrincipal(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 1) {
      return true;
    }
    return false;
  }

  tc_schema::Principal CDMRecordParser::getPrincipal(const tc_schema::TCCDMDatum& record) {
    if (isPrincipal(record)) {
      return record.datum.get_Principal();
    } else {
      throw std::invalid_argument("Record is not of type Principal.");
    }
  }

  bool CDMRecordParser::isIpcObject(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 6) {
      return true;
    }
    return false;
  }

  tc_schema::IpcObject CDMRecordParser::getIpcObject(const tc_schema::TCCDMDatum& record) {
    if (isIpcObject(record)) {
      return record.datum.get_IpcObject();
    } else {
      throw std::invalid_argument("Record is not of type IpcObject.");
    }
  }

  bool CDMRecordParser::isRegistryKeyObject(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 7) {
      return true;
    }
    return false;
  }

  tc_schema::RegistryKeyObject CDMRecordParser::getRegistryKeyObject(const tc_schema::TCCDMDatum& record) {
    if (isRegistryKeyObject(record)) {
      return record.datum.get_RegistryKeyObject();
    } else {
      throw std::invalid_argument("Record is not of type RegistryKeyObject.");
    }
  }

  bool CDMRecordParser::isHost(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 0) {
      return true;
    }
    return false;
  }

  tc_schema::Host CDMRecordParser::getHost(const tc_schema::TCCDMDatum& record) {
    if (isHost(record)) {
      return record.datum.get_Host();
    } else {
      throw std::invalid_argument("Record is not of type Host.");
    }
  }

  bool CDMRecordParser::isPacketSocketObject(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 8) {
      return true;
    }
    return false;
  }

  tc_schema::PacketSocketObject CDMRecordParser::getPacketSocketObject(const tc_schema::TCCDMDatum& record) {
    if (isPacketSocketObject(record)) {
      return record.datum.get_PacketSocketObject();
    } else {
      throw std::invalid_argument("Record is not of type PacketSocketObject.");
    }
  }

  bool CDMRecordParser::isEndMarker(const tc_schema::TCCDMDatum& record) {
    if (record.datum.idx() == 15) {
      return true;
    }
    return false;
  }

  tc_schema::EndMarker CDMRecordParser::getEndMarker(const tc_schema::TCCDMDatum& record) {
    if (isEndMarker(record)) {
      return record.datum.get_EndMarker();
    } else {
      throw std::invalid_argument("Record is not of type EndMarker.");
    }
  }

  std::string CDMRecordParser::getType(const tc_schema::TCCDMDatum& cdmRecord) {
    if (isProvenanceTagNode(cdmRecord)) {
      return "ProvenanceTagNode";
    } else if (isUnknownProvenanceNode(cdmRecord)) {
      return "UnknownProvenanceNode";
    } else if (isTimeMarker(cdmRecord)) {
      return "TimeMarker";
    } else if (isSubject(cdmRecord)) {
      return "Subject";
    } else if (isEvent(cdmRecord)) {
      return "Event";
    } else if (isNetFlowObject(cdmRecord)) {
      return "NetFlowObject";
    } else if (isFileObject(cdmRecord)) {
      return "FileObject";
    } else if (isSrcSinkObject(cdmRecord)) {
      return "SrcSinkObject";
    } else if (isMemoryObject(cdmRecord)) {
      return "MemoryObject";
    } else if (isPrincipal(cdmRecord)) {
      return "Principal";
    } else if (isIpcObject(cdmRecord)) {
      return "IpcObject";
    } else if (isRegistryKeyObject(cdmRecord)) {
      return "RegistryKeyObject";
    } else if (isHost(cdmRecord)) {
      return "Host";
    } else if (isPacketSocketObject(cdmRecord)) {
      return "PacketSocketObject";
    } else if (isEndMarker(cdmRecord)) {
      return "EndMarker";
    } else {
      std::string unk = "Unknown:" + std::to_string(cdmRecord.datum.idx());
      return unk;
    }
  }
}
