#include "asdf.h"

#include "gtest/gtest.h"

#include <filesystem>
#include <stdexcept>

namespace {
  class ASDFTestC : public ::testing::Test {
    protected:
    std::filesystem::path _temp_path;
    virtual void SetUp() {
      asdf_clear_error();
      _temp_path = {std::filesystem::temp_directory_path() /= std::tmpnam(nullptr)};

      // Attempt to create the directory.
      if (!std::filesystem::create_directories(_temp_path)) {
        throw std::runtime_error("directory could not be created.");
      }
    }

    virtual void TearDown() {
      std::filesystem::remove_all(_temp_path);
    };
  };

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

      asdf_clear_error();
      lib_divide(numerators.at(index), denominators.at(index), &remainder, &result);
      EXPECT_EQ(asdf_get_error(), 0);
      EXPECT_EQ(remainder, remainders.at(index));
      EXPECT_EQ(result, divisions.at(index));
    }
  };
}

TEST_F(ASDFTestC, Open) {
  auto path = _temp_path / "test.asdf";
  auto handle = asdf_read(path.string().c_str());
  EXPECT_EQ(handle, nullptr);
  EXPECT_EQ(asdf_get_error(), 3);
  const char* err = nullptr;
  asdf_get_error_details(3, &err);
  EXPECT_EQ(strcmp(err, "File does not exist"), 0);
}

TEST_F(DividerTestC, Long_DivideBy_Long) {
  verify(3);
}
