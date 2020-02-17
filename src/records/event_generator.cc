// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/event_generator.h"

namespace tc_records {

EventGenerator::EventGenerator() {}

tc_schema::Event
EventGenerator::getRandomEvent(uint32_t numKvPairs) {
  tc_schema::Event event;
  event.uuid = ug.getRandomUuid();
  event.sequence = this->getRandomSequence();
  event.type = this->getRandomType();
  event.threadId = this->getRandomThreadId();
  event.subject = this->getRandomSubject();
  event.timestampNanos = tg.getRandomTimestamp();
  event.predicateObject = this->getRandomPredicateObject();
  event.predicateObjectPath = this->getRandomPredicateObjectPath();
  event.predicateObject2 = this->getRandomPredicateObject2();
  event.predicateObject2Path = this->getRandomPredicateObject2Path();
  event.parameters = this->getRandomParameters();
  event.location = this->getRandomLocation();
  event.size = this->getRandomSize();
  event.programPoint = this->getRandomProgramPoint();
  event.properties = this->getRandomProperties(numKvPairs);
  event.names = this->getRandomNames();

  return event;
}

tc_schema::Event::sequence_t
EventGenerator::getRandomSequence() {
  tc_schema::Event::sequence_t s;
  if (oeg.elementIsNull())
    s.set_null();
  else
    s.set_long(rand() % 0x0fffffffffffffff);
  return s;
}

tc_schema::Event::subject_t
EventGenerator::getRandomSubject() {
  tc_schema::Event::subject_t s;
  if (oeg.elementIsNull())
    s.set_null();
  else
    s.set_UUID(ug.getRandomUuid());
  return s;
}

tc_schema::Event::predicateObjectPath_t
EventGenerator::getRandomPredicateObjectPath() {
  tc_schema::Event::predicateObjectPath_t pop;
  if (oeg.elementIsNull())
    pop.set_null();
  else
    pop.set_string("/path/to/glory");
  return pop;
}

tc_schema::Event::predicateObject_t
EventGenerator::getRandomPredicateObject() {
  tc_schema::Event::predicateObject_t po;
  if (oeg.elementIsNull())
    po.set_null();
  else
    po.set_UUID(ug.getRandomUuid());
  return po;
}


tc_schema::Event::predicateObject2_t
EventGenerator::getRandomPredicateObject2() {
  tc_schema::Event::predicateObject2_t po2;
  if (oeg.elementIsNull())
    po2.set_null();
  else
    po2.set_UUID(ug.getRandomUuid());
  return po2;
}

tc_schema::Event::predicateObject2Path_t
EventGenerator::getRandomPredicateObject2Path() {
  tc_schema::Event::predicateObject2Path_t po2p;
  if (oeg.elementIsNull())
    po2p.set_null();
  else
    po2p.set_string("/path/to/failure");
  return po2p;
}

tc_schema::EventType
EventGenerator::getRandomType() {
  // FIXME: actually randomize this
  return tc_schema::EVENT_ACCEPT;
}

tc_schema::Event::threadId_t
EventGenerator::getRandomThreadId() {
  tc_schema::Event::threadId_t tid;
  if (oeg.elementIsNull()) {
    tid.set_null();
  } else {
    tid.set_int(rand() % 0x0fffffff);
  }
  return tid;
}

tc_schema::Event::names_t
EventGenerator::getRandomNames() {
  tc_schema::Event::names_t names;
  if (oeg.elementIsNull()) {
    names.set_null();
  } else {
    // FIXME: actually make this random
    std::vector<std::string> v{"Random string 1", "Random string 2"};
    names.set_array(v);
  }
  return names;
}

tc_schema::Event::parameters_t
EventGenerator::getRandomParameters() {
  tc_schema::Event::parameters_t params;
  if (oeg.elementIsNull())
    params.set_null();
  else {
    std::vector<tc_schema::Value> vals;
    int elts = rand() % 8;
    for (int i = 0; i < elts; i++) {
      vals.push_back(vg.getRandomValue());
    }
    params.set_array(vals);
  }
  return params;
}

tc_schema::Event::location_t
EventGenerator::getRandomLocation() {
  tc_schema::Event::location_t loc;
  if (oeg.elementIsNull())
    loc.set_null();
  else
    loc.set_long(rand() % 0x0fffffffffffffff);
  return loc;
}

tc_schema::Event::size_t
EventGenerator::getRandomSize() {
  tc_schema::Event::size_t sz;
  if (oeg.elementIsNull())
    sz.set_null();
  else
    sz.set_long(rand() % 0x0fffffffffffffff);
  return sz;

}

tc_schema::Event::programPoint_t
EventGenerator::getRandomProgramPoint() {
  tc_schema::Event::programPoint_t ppt;
  if (oeg.elementIsNull())
    ppt.set_null();
  else
    // FIXME: actually make this random
    ppt.set_string("My program point");
  return ppt;

}

tc_schema::Event::properties_t
EventGenerator::getRandomProperties(uint32_t numKvPairs) {
  tc_schema::Event::properties_t props;
  if (numKvPairs == 0 && oeg.elementIsNull())
    props.set_null();
  else
    props.set_map(pg.getRandomMap(numKvPairs));
  return props;
}

}  // namespace tc_records
