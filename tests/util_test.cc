// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "util/timeconvert.h"

#include <exception>

#include "gtest/gtest.h"

class UtilTest : public ::testing::Test {
  protected:
    int64_t ts;
    std::string iso8601Str;

    UtilTest() { };

    void SetUp() {
      iso8601Str = "2016-12-01T01:02:03.456Z";
      ts = 1480554123456;
    }
};

TEST_F(UtilTest, TimestampToTimepointTest) {
  auto tp = tc_util::toTimePoint(this->ts);
  auto testIso8601Str = tc_util::toIso8601(tp);
  EXPECT_EQ(testIso8601Str, this->iso8601Str);
}

TEST_F(UtilTest, Iso8601ToTimepointTest) {
  auto tp = tc_util::toTimePoint(this->iso8601Str);
  auto testTs = tc_util::toMsSinceEpoch(tp);
  EXPECT_EQ(testTs, ts);
}

TEST_F(UtilTest, Iso8601ToTimestampTest) {
  auto testTs = tc_util::toMsSinceEpoch(this->iso8601Str);
  EXPECT_EQ(testTs, ts);
}

TEST_F(UtilTest, TimestamptToIso8601Test) {
  auto testIso8601Str = tc_util::toIso8601(this->ts);
  EXPECT_EQ(testIso8601Str, this->iso8601Str);
}

TEST_F(UtilTest, Iso8601NoTzTest) {
  ASSERT_THROW(tc_util::toTimePoint("2016-12-01T01:02:03.456"), std::invalid_argument);
}

TEST_F(UtilTest, Iso8601NoMsTest) {
  ASSERT_THROW(tc_util::toTimePoint("2016-12-01T01:02:03Z"), std::invalid_argument);
}

TEST_F(UtilTest, Iso8601MissingTTest) {
  ASSERT_THROW(tc_util::toTimePoint("2016-12-01 01:02:03.456"), std::invalid_argument);
}

TEST_F(UtilTest, Iso8601MissingDotTest) {
  ASSERT_THROW(tc_util::toTimePoint("2016-12-01T01:02:03:456"), std::invalid_argument);
}

TEST_F(UtilTest, BadStringTest1) {
  ASSERT_THROW(tc_util::toTimePoint("1234567890"), std::invalid_argument);
}

TEST_F(UtilTest, BadStringTest2) {
  ASSERT_THROW(tc_util::toTimePoint("2016-12-01T01:02:03...............456Z"), std::invalid_argument);
}

TEST_F(UtilTest, BadStringTest3) {
  ASSERT_THROW(tc_util::toTimePoint("2016-12-1T1:2:3.456Z"), std::invalid_argument);
}
