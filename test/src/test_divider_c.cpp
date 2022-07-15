#include "division.h"

#include "gtest/gtest.h"

namespace {
  typedef std::vector<int64_t> VI;
  class DividerTestC : public ::testing::Test {

  protected:
    VI numerators   {5, 9, 17, 933345453464353416L};
    VI denominators {2, 3, 19, 978737423423423499L};
    VI divisions    {2, 3, 0, 0};
    VI remainders   {1, 0, 17, 933345453464353416};

    virtual void SetUp() {};

    virtual void TearDown() {};

    virtual void verify(int index) {
      int64_t remainder, result;

      lib_clear_error();
      lib_divide(numerators.at(index), denominators.at(index), &remainder, &result);
      EXPECT_EQ(lib_get_error(), 0);
      EXPECT_EQ(remainder, remainders.at(index));
      EXPECT_EQ(result, divisions.at(index));
    }
  };
}

TEST_F(DividerTestC, 5_DivideBy_2) {
  verify(0);
}

TEST_F(DividerTestC, 9_DivideBy_3) {
  verify(1);
}

TEST_F(DividerTestC, 17_DivideBy_19) {
  verify(2);
}

TEST_F(DividerTestC, Long_DivideBy_Long) {
  verify(3);
}

TEST_F(DividerTestC, DivisionByZero) {
  lib_clear_error();
  int64_t remainder, result;
  lib_divide(1, 0, &remainder, &result);
  EXPECT_EQ(lib_get_error(), 2);
  const char* err = nullptr;
  lib_get_error_details(2, &err);
  EXPECT_EQ(strcmp(err, "Division by zero is illegal"), 0);
}
