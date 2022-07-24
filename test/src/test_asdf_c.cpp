#include "asdf.h"

#define TEST_NO_MAIN
#include "acutest.h"

#include <filesystem>
#include <stdexcept>

namespace {
  class TempDirectory {
    public:
    std::filesystem::path _temp_path;
    TempDirectory() {
      asdf_clear_error();
      _temp_path = {std::filesystem::temp_directory_path() /= std::tmpnam(nullptr)};

      // Attempt to create the directory.
      if (!std::filesystem::create_directories(_temp_path)) {
        throw std::runtime_error("directory could not be created.");
      }
    }

    virtual ~TempDirectory() {
      std::filesystem::remove_all(_temp_path);
    };
  };
}

void test_asdf_c_basic() {
  TempDirectory temp_directory;
  auto path = temp_directory._temp_path / "test.asdf";
  auto handle = asdf_read(path.string().c_str());
  TEST_CHECK(handle == nullptr);
  TEST_CHECK(asdf_get_error() == 3);
  const char* err = nullptr;
  asdf_get_error_details(3, &err);
  TEST_CHECK(strcmp(err, "File does not exist") == 0);
}
