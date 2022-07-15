#pragma once

#include "division.h"

#include <stdexcept>

class LibException : public exception {
  std::string _what;
  int32_t _error;
public:
  LibException(int32_t errorcode) : _error(errorcode) {
    char* error;
    lib_get_error_details(_error, &error);
    if (error != nullptr)
      _what = error;
  }
  virtual const char *what() const throw() {
    return _what.c_str();
  }
};

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

  ~Division() {
  };

  DivisionResult divide() {
    lib_clear_error();
    DivisionResult result;
    lib_divide(fraction.numerator, fraction.denominator, &result.remainder, &result.division);
    int32_t errorcode = lib_get_error();
    if (errorcode != 0) {
      lib_clear_error();
      throw LibException(errorcode);
    }
    return result;
  }

protected:
  Fraction       fraction;
  DivisionResult result;
};
