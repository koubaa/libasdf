#include "asdf.h"

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
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
    "File permission error",
    "File does not exist"
  };
  if (error == nullptr)
    return;

  if (val == 0 || val > errors.size())
    *error = nullptr;
  *error = errors[val-1].c_str();
}

struct asdf_file {
  int valid; // 0 if the file is no longer used.
  FILE* file_handle; // file stream, valid while active.
  int mode; // 0 - read, 1 - write
};

// asdf file handles are integers into this map
static int64_t next_active_file_handle = 1;
static std::map<int64_t, asdf_file> active_files;

/**
 * @brief reads the file with the given name
 * 
 * @param name name of file
 * @return asdf_file_handle 
 * @remark returns nullptr and sets error if the file cannot be opened.
 *         TODO - make it threadsafe by locking around active_files
 */
asdf_file_handle asdf_read(const char* name) {
  if (!std::filesystem::exists(name)) {
    asdf_set_error(3);
    return nullptr;
  }

  FILE* p_file = fopen(name, "r");
  asdf_file new_handle {
    .valid = 1,
    .file_handle = p_file,
    .mode = 0
  };

  //this is *NOT* threadsafe
  auto handle = next_active_file_handle++;
  active_files[handle] = new_handle;
  return (asdf_file_handle)handle;
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
