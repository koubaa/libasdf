#include "division.h"
#include "division.hpp"

#include "gtest/gtest.h"

#define VI std::vector<long long>

class DividerTest : public ::testing::Test {

protected:
  VI numerators   = {5, 9, 17, 933345453464353416L};
  VI denominators = {2, 3, 19, 978737423423423499L};
  VI divisions    = {2, 3, 0, 0};
  VI remainders   = {1, 0, 17, 933345453464353416};

  virtual void SetUp() {
  };

  virtual void TearDown() {
  };

  virtual void verify_old(int index) {
    Fraction       f        = Fraction {numerators.at(index), denominators.at(index)};
    DivisionResult expected = DivisionResult {divisions.at(index), remainders.at(index)};
    DivisionResult result   = Division(f).divide();
    EXPECT_EQ(result.division, expected.division);
    EXPECT_EQ(result.remainder, expected.remainder);
  }

  virtual void verify(int index) {
    int64_t remainder, result;

    lib_clear_error();
    lib_divide(numerators.at(index), denominators.at(index), &remainder, &result);
    EXPECT_EQ(lib_get_error(), 0);
    EXPECT_EQ(remainder, remainders.at(index));
    EXPECT_EQ(result, divisions.at(index));
  }
};

TEST_F(DividerTest, 5_DivideBy_2) {
  verify(0);
}

TEST_F(DividerTest, 9_DivideBy_3) {
  verify(1);
}

TEST_F(DividerTest, 17_DivideBy_19) {
  verify(2);
}

TEST_F(DividerTest, Long_DivideBy_Long) {
  verify(3);
}

TEST_F(DividerTest, DivisionByZeroOld) {
  Division d = Division(Fraction{1, 0});
  try {
    d.divide();
    FAIL() << "Expected divide() method to throw LibException with code 2";
  } catch (LibException const &err) {
    EXPECT_EQ(err.what(), std::string("Division by zero is illegal"));
  }
  catch (...) {
    FAIL() << "Expected DivisionByZeroException!";
  }
}

TEST_F(DividerTest, DivisionByZero) {
  lib_clear_error();
  int64_t remainder, result;
  lib_divide(1, 0, &remainder, &result);
  EXPECT_EQ(lib_get_error(), 2);
  const char* err = nullptr;
  lib_get_error_details(2, &err);
  EXPECT_EQ(strcmp(err, "Division by zero is illegal"), 0);
}
