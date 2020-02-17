// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/packet_socket_object_generator.h"

namespace tc_records {

PacketSocketObjectGenerator::PacketSocketObjectGenerator() {}

tc_schema::PacketSocketObject
PacketSocketObjectGenerator::getRandomPacketSocketObject(uint32_t numKvPairs) {
  tc_schema::PacketSocketObject pso;
  pso.uuid = ug.getRandomUuid();
  pso.baseObject = aog.getRandomAbstractObject(numKvPairs);
  pso.proto = this->getRandomProto();
  pso.ifIndex = this->getRandomIfIndex();
  pso.haType = this->getRandomHaType();
  pso.pktType = this->getRandomPktType();
  pso.addr = this->getRandomAddr();

  return pso;
}

boost::array<uint8_t, 2>
PacketSocketObjectGenerator::getRandomProto() {
  boost::array<uint8_t, 2>v = {(uint8_t) (rand()%256),
                               (uint8_t) (rand()%256)};
  return v;
}

int32_t
PacketSocketObjectGenerator::getRandomIfIndex() {
  return (int32_t) rand() % 0x0fffffff;
}

boost::array<uint8_t, 2>
PacketSocketObjectGenerator::getRandomHaType() {
  boost::array<uint8_t, 2>v = {(uint8_t) (rand()%256),
                               (uint8_t) (rand()%256)};
  return v;
}

boost::array<uint8_t, 1>
PacketSocketObjectGenerator::getRandomPktType() {
  boost::array<uint8_t, 1>v = {(uint8_t) (rand()%256)};
  return v;
}

std::vector<uint8_t>
PacketSocketObjectGenerator::getRandomAddr() {
  std::vector<uint8_t>v = {(uint8_t) (rand()%256),
                           (uint8_t) (rand()%256),
                           (uint8_t) (rand()%256),
                           (uint8_t) (rand()%256),
                           (uint8_t) (rand()%256),
                           (uint8_t) (rand()%256)};
  return v;
}

}  // namespace tc_records
