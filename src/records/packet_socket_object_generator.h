// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_PACKET_SOCKET_OBJECT_GENERATOR_H_
#define TC_RECORDS_PACKET_SOCKET_OBJECT_GENERATOR_H_

#include "records/abstract_object_generator.h"
#include "records/uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class PacketSocketObjectGenerator {
    AbstractObjectGenerator aog;
    UuidGenerator ug;

    boost::array<uint8_t, 2> getRandomProto();
    int32_t getRandomIfIndex();
    boost::array<uint8_t, 2> getRandomHaType();
    boost::array<uint8_t, 1> getRandomPktType();
    std::vector<uint8_t> getRandomAddr();

  public:
    PacketSocketObjectGenerator();
    tc_schema::PacketSocketObject getRandomPacketSocketObject(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_PACKET_SOCKET_OBJECT_GENERATOR_H_
