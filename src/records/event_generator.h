// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_EVENT_GENERATOR_H_
#define TC_RECORDS_EVENT_GENERATOR_H_

#include "records/optional_element_generator.h"
#include "records/property_generator.h"
#include "records/timestamp_generator.h"
#include "records/uuid_generator.h"
#include "records/value_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class EventGenerator {
    OptionalElementGenerator oeg;
    PropertyGenerator pg;
    TimestampGenerator tg;
    UuidGenerator ug;
    ValueGenerator vg;

    tc_schema::EventType getRandomType();
    tc_schema::Event::sequence_t getRandomSequence();
    tc_schema::Event::subject_t getRandomSubject();
    tc_schema::Event::threadId_t getRandomThreadId();
    tc_schema::Event::names_t getRandomNames();
    tc_schema::Event::parameters_t getRandomParameters();
    tc_schema::Event::location_t getRandomLocation();
    tc_schema::Event::size_t getRandomSize();
    tc_schema::Event::programPoint_t getRandomProgramPoint();
    tc_schema::Event::properties_t getRandomProperties(uint32_t numKvPairs);
    tc_schema::Event::predicateObject_t getRandomPredicateObject();
    tc_schema::Event::predicateObjectPath_t getRandomPredicateObjectPath();
    tc_schema::Event::predicateObject2_t getRandomPredicateObject2();
    tc_schema::Event::predicateObject2Path_t getRandomPredicateObject2Path();

  public:
    EventGenerator();
    tc_schema::Event getRandomEvent(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_EVENT_GENERATOR_H_
