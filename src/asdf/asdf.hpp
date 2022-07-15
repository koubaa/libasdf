#pragma once

#include "asdf.h"

#include <cstdint>
#include <stdexcept>
#include <string>

namespace asdf {
  class error : public std::exception {
    std::string _what;
    int32_t _error;
  public:
    error(int32_t errorcode) : _error(errorcode) {
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
      throw asdf::error(errorcode);
    }
    return result;
  }

protected:
  Fraction       fraction;
  DivisionResult result;
};
