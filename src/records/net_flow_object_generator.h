// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_NET_FLOW_OBJECT_GENERATOR_H_
#define TC_RECORDS_NET_FLOW_OBJECT_GENERATOR_H_

#include "records/abstract_object_generator.h"
#include "records/optional_element_generator.h"
#include "records/uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class NetFlowObjectGenerator {
    AbstractObjectGenerator aog;
    OptionalElementGenerator oeg;
    UuidGenerator ug;

    std::string getRandomLocalAddress();
    int32_t getRandomLocalPort();
    std::string getRandomRemoteAddress();
    int32_t getRandomRemotePort();
    tc_schema::NetFlowObject::ipProtocol_t getRandomIpProtocol();
    tc_schema::NetFlowObject::fileDescriptor_t getRandomFileDescriptor();

  public:
    NetFlowObjectGenerator();
    tc_schema::NetFlowObject getRandomNetFlowObject(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_NET_FLOW_OBJECT_GENERATOR_H_
