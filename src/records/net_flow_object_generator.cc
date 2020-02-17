// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/net_flow_object_generator.h"

namespace tc_records {

NetFlowObjectGenerator::NetFlowObjectGenerator() {}

tc_schema::NetFlowObject
NetFlowObjectGenerator::getRandomNetFlowObject(uint32_t numKvPairs) {
  tc_schema::NetFlowObject nfObj;
  nfObj.uuid = ug.getRandomUuid();
  nfObj.baseObject = aog.getRandomAbstractObject(numKvPairs);

  // This is optional, but something needs to be set in order
  // for things to work for the python bindings
  nfObj.localAddress.set_string(this->getRandomLocalAddress());

  if (oeg.elementIsNull())
    nfObj.localPort.set_null();
  else
    nfObj.localPort.set_int(this->getRandomLocalPort());

  if (oeg.elementIsNull())
    nfObj.remoteAddress.set_null();
  else
    nfObj.remoteAddress.set_string(this->getRandomRemoteAddress());

  if (oeg.elementIsNull())
    nfObj.remotePort.set_null();
  else
    nfObj.remotePort.set_int(this->getRandomRemotePort());

  nfObj.ipProtocol = this->getRandomIpProtocol();
  nfObj.fileDescriptor = this->getRandomFileDescriptor();

  if (oeg.elementIsNull())
    nfObj.initTcpSeqNum.set_null();
  else
    nfObj.initTcpSeqNum.set_int(1234567);

  return nfObj;
}

std::string
NetFlowObjectGenerator::getRandomLocalAddress() {
  // FIXME: actually randomize this
  return std::string("192.168.1.87");
}

int32_t
NetFlowObjectGenerator::getRandomLocalPort() {
  return rand() % 0xffff;
}

std::string
NetFlowObjectGenerator::getRandomRemoteAddress() {
  // FIXME: actually randomize this
  return std::string("1.2.3.4");
}

int32_t
NetFlowObjectGenerator::getRandomRemotePort() {
  return rand() % 0xffff;
}

tc_schema::NetFlowObject::ipProtocol_t
NetFlowObjectGenerator::getRandomIpProtocol() {
  tc_schema::NetFlowObject::ipProtocol_t proto;
  if (oeg.elementIsNull())
    proto.set_null();
  else
    // FIXME: actually randomize this
    // 6 corresponds to TCP.
    proto.set_int(6);
  return proto;
}

tc_schema::NetFlowObject::fileDescriptor_t
NetFlowObjectGenerator::getRandomFileDescriptor() {
  tc_schema::NetFlowObject::fileDescriptor_t fd;
  if (oeg.elementIsNull())
    fd.set_null();
  else
    fd.set_int(rand() % 0xffff);
  return fd;
}

}  // namespace tc_records
