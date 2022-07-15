#include "asdf.h"

#include <cstdint>
#include <filesystem>
#include <map>
#include <string>
#include <vector>

thread_local int32_t asdf_errno;

static void asdf_set_error(int32_t val) {
  asdf_errno = val;
}
void asdf_clear_error() {
  asdf_errno = 0;
}

int32_t asdf_get_error() {
  return asdf_errno;
}

void asdf_get_error_details(int32_t val, const char** error) {
  static const std::vector<std::string> errors {
    "Argument null error",
    "Division by zero is illegal",
    "File does not exist"
  };
  if (error == nullptr)
    return;

  if (val == 0 || val > errors.size())
    *error = nullptr;
  *error = errors[val-1].c_str();
}

struct asdf_file {
  FILE* handle;
  int mode;
};

//todo store handles somehow
thread_local asdf_file active_file;


/**
 * @brief reads the file with the given name
 * 
 * @param name 
 * @return asdf_file_handle 
 * @remark returns nullptr and sets error if the file cannot be opened.
 */
asdf_file_handle asdf_read(const char* name) {
  if (!std::filesystem::exists(name)) {
    asdf_set_error(3);
    return nullptr;
  }
  return nullptr;
}

void lib_divide(
  int64_t numerator,
  int64_t denominator,
  int64_t* remainder,
  int64_t* result)
{
  if (!remainder || !result)
    asdf_set_error(1);

  if (denominator == 0L)
    asdf_set_error(2);

  *result = numerator / denominator;
  *remainder = numerator % denominator;
}
