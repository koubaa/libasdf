#pragma once

#include "asdf.h"

#include <cstdint>
#include <filesystem>
#include <stdexcept>
#include <string>

namespace {
  namespace asdf {
    class Error : public std::exception {
      std::string _what;
      int32_t _error;
    public:
      Error(int32_t errorcode) : _error(errorcode) {
        const char* error;
        asdf_get_error_details(_error, &error);
        if (error != nullptr)
          _what = error;
      }
      virtual const char *what() const throw() {
        return _what.c_str();
      }
      int32_t code() const {
        return _error;
      }
    };

    namespace detail {
      static void throw_if_error() {
        auto errorcode = asdf_get_error();
        if (errorcode != 0) {
          throw asdf::Error(errorcode);
        }
      }
    }

    class File {
      asdf_file_handle _handle;

      public:
      enum Mode {
        READ = 0
      };

      File(std::filesystem::path path, Mode mode) {
        asdf_clear_error();
        if (mode == READ) {
          _handle = asdf_read(path.string().c_str());
        } else {
          throw std::runtime_error("Unexpected File mode argument");
        }
        detail::throw_if_error();
      }
      virtual ~File() {
        asdf_clear_error();
        //asdf_close(_handle);
        detail::throw_if_error();
      }
    };
  }
}
