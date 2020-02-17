// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_CDM_RECORD_GENERATOR_H_
#define TC_RECORDS_CDM_RECORD_GENERATOR_H_

#include "records/end_marker_generator.h"
#include "records/event_generator.h"
#include "records/file_object_generator.h"
#include "records/host_generator.h"
#include "records/instrumentation_source_generator.h"
#include "records/memory_object_generator.h"
#include "records/net_flow_object_generator.h"
#include "records/packet_socket_object_generator.h"
#include "records/principal_generator.h"
#include "records/provenance_tag_node_generator.h"
#include "records/registry_key_object_generator.h"
#include "records/src_sink_object_generator.h"
#include "records/subject_generator.h"
#include "records/time_marker_generator.h"
#include "records/unit_dependency_generator.h"
#include "records/ipc_object_generator.h"
#include "records/unknown_provenance_node_generator.h"
#include "records/uuid_generator.h"
#include "serialization/avro_generic_serializer.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class CDMRecordGenerator {
  protected:
    InstrumentationSourceGenerator isg;
    ProvenanceTagNodeGenerator ptng;
    SubjectGenerator sg;
    EventGenerator eg;
    NetFlowObjectGenerator nfog;
    FileObjectGenerator fog;
    SrcSinkObjectGenerator ssog;
    MemoryObjectGenerator mog;
    PrincipalGenerator pg;
    RegistryKeyObjectGenerator rkog;
    TimeMarkerGenerator tmg;
    UnitDependencyGenerator udg;
    IpcObjectGenerator iog;
    HostGenerator hg;
    PacketSocketObjectGenerator psog;
    EndMarkerGenerator emg;
    UnknownProvenanceNodeGenerator upng;
    UuidGenerator ug;
    static const std::string CDM_VERSION;
    static const uint32_t NUM_DATA_TYPES;
    static const uint32_t SESSION_NUM;

  public:
    CDMRecordGenerator();
    tc_schema::TCCDMDatum getRandomRecord(uint32_t numKvPairs);

    tc_schema::TCCDMDatum getRandomProvenanceTagNodeRecord(
      uint32_t numKvPairs);
    tc_schema::TCCDMDatum getRandomSubjectRecord(uint32_t numKvPairs);
    tc_schema::TCCDMDatum getRandomEventRecord(uint32_t numKvPairs);
    tc_schema::TCCDMDatum getRandomNetFlowObjectRecord(uint32_t numKvPairs);
    tc_schema::TCCDMDatum getRandomFileObjectRecord(uint32_t numKvPairs);
    tc_schema::TCCDMDatum getRandomSrcSinkObjectRecord(uint32_t numKvPairs);
    tc_schema::TCCDMDatum getRandomMemoryObjectRecord(uint32_t numKvPairs);
    tc_schema::TCCDMDatum getRandomPrincipalRecord(uint32_t numKvPairs);
    tc_schema::TCCDMDatum getRandomRegistryKeyObjectRecord(uint32_t numKvPairs);
    tc_schema::TCCDMDatum getRandomIpcObjectRecord(uint32_t numKvPairs);
    tc_schema::TCCDMDatum getRandomPacketSocketObjectRecord(uint32_t numKvPairs);
    tc_schema::TCCDMDatum getRandomTimeMarkerRecord();
    tc_schema::TCCDMDatum getRandomUnitDependencyRecord();
    tc_schema::TCCDMDatum getRandomHostRecord();
    tc_schema::TCCDMDatum getRandomEndMarkerRecord();
    tc_schema::TCCDMDatum getRandomUnknownProvenanceNodeRecord(uint32_t numKvPairs);

    uint32_t getAverageRecordSize(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_CDM_RECORD_GENERATOR_H_
