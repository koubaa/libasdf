#include "asdf.hpp"

#include "gtest/gtest.h"

namespace {
  typedef std::vector<int64_t> VI;
  class DividerTestCXX : public ::testing::Test {

    protected:
    VI numerators   {5, 9, 17, 933345453464353416L};
    VI denominators {2, 3, 19, 978737423423423499L};
    VI divisions    {2, 3, 0, 0};
    VI remainders   {1, 0, 17, 933345453464353416};

    virtual void SetUp() {};

    virtual void TearDown() {};

    virtual void verify(int index) {
      Fraction       f        = Fraction {numerators.at(index), denominators.at(index)};
      DivisionResult expected = DivisionResult {divisions.at(index), remainders.at(index)};
      DivisionResult result   = Division(f).divide();
      EXPECT_EQ(result.division, expected.division);
      EXPECT_EQ(result.remainder, expected.remainder);
    }
  };
}

TEST_F(DividerTestCXX, 5_DivideBy_2) {
  verify(0);
}

TEST_F(DividerTestCXX, 9_DivideBy_3) {
  verify(1);
}

TEST_F(DividerTestCXX, 17_DivideBy_19) {
  verify(2);
}

TEST_F(DividerTestCXX, Long_DivideBy_Long) {
  verify(3);
}

TEST_F(DividerTestCXX, DivisionByZero) {
  Division d = Division(Fraction{1, 0});
  try {
    d.divide();
    FAIL() << "Expected divide() method to throw LibException with code 2";
  } catch (asdf::error const &err) {
    EXPECT_EQ(err.what(), std::string("Division by zero is illegal"));
  }
  catch (...) {
    FAIL() << "Expected DivisionByZeroException!";
  }
}
