#include "asdf.h"

#include "test_utils.h"
#define TEST_NO_MAIN
#include "acutest.h"

void test_asdf_c_open_fail() {
  TempDirectory temp_directory;
  auto path = temp_directory._temp_path / "test.asdf";
  asdf_clear_error();
  auto handle = asdf_read(path.string().c_str());
  TEST_CHECK(handle == nullptr);
  TEST_CHECK(asdf_get_error() == 3);
  const char* err = nullptr;
  asdf_get_error_details(3, &err);
  TEST_CHECK(strcmp(err, "File does not exist") == 0);

  // TODO test a file that exists but cannot be opened.
}
