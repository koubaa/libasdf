#pragma once

#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <unistd.h>

class TempDirectory {
  public:
  std::filesystem::path _temp_path;
  TempDirectory() {
    auto _temp_path_template = std::filesystem::temp_directory_path() / "asdf.XXXXXX";

    // Attempt to create the directory.
    char* dir_name = mkdtemp((char*)_temp_path_template.string().c_str());
    if (!dir_name) {
      throw std::runtime_error("directory could not be created.");
    }

    _temp_path = dir_name;
  }

  virtual ~TempDirectory() {
    std::filesystem::remove_all(_temp_path);
  };
};