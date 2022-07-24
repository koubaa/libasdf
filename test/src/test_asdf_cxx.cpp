#include "asdf.hpp"

#include "test_utils.h"
#define TEST_NO_MAIN
#include "acutest.h"

void test_asdf_cxx_open_fail() {
  TempDirectory temp_directory;
  auto path = temp_directory._temp_path / "test.asdf";
  TEST_EXCEPTION(asdf::File(path, asdf::File::READ), asdf::Error);
}