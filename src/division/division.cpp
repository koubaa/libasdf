#include "division.h"

#include <string>
#include <thread>
#include <vector>

thread_local int32_t lib_errno;

static void lib_set_error(int32_t val) {
  lib_errno = val;
}
void lib_clear_error() {
  lib_errno = 0;
}

int32_t lib_get_error() {
  return lib_errno;
}

void lib_get_error_details(int val, const char** error) {
  static const std::vector<std::string> errors {
    "Argument null error",
    "Division by zero is illegal"
  };
  if (error == nullptr)
    return;

  if (val == 0 || val > errors.size())
    *error = nullptr;
  *error = errors[val-1].c_str();
}

void lib_divide(
  int64_t numerator,
  int64_t denominator,
  int64_t* remainder,
  int64_t* result)
{
  if (!remainder || !result)
    lib_set_error(1);

  if (denominator == 0L)
    lib_set_error(2);

  *result = numerator / denominator;
  *remainder = numerator % denominator;
}
