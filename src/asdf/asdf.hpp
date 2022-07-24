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

struct Fraction {
  int64_t numerator;
  int64_t denominator;
};

struct DivisionResult {
  int64_t division;
  int64_t remainder;

  friend bool operator==(const DivisionResult &lhs, const DivisionResult &rhs) {
    return lhs.division == rhs.division ? lhs.remainder < rhs.remainder : lhs.division < rhs.division;
  }
};

class Division {
public:
  explicit Division(Fraction fraction) {
    this->fraction = fraction;
  }

  DivisionResult divide() {
    asdf_clear_error();
    DivisionResult result;
    lib_divide(fraction.numerator, fraction.denominator, &result.remainder, &result.division);
    int32_t errorcode = asdf_get_error();
    if (errorcode != 0) {
      asdf_clear_error();
      throw asdf::Error(errorcode);
    }
    return result;
  }

protected:
  Fraction       fraction;
  DivisionResult result;
};
