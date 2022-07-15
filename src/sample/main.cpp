#include "asdf.hpp"

#include <iostream>

int main(int argc, const char *argv[]) {
  static const char *const USAGE = "Usage:\n\tdivider <numerator> <denominator>\n\nDescription:\n\tComputes the result of a fractional division,\n\tand reports both the result and the remainder.\n";

  Fraction f;

  // ensure the correct number of parameters are used.
  if (argc < 3) {
    std::cout << USAGE;
    return 1;
  }

  f.numerator = atoll(argv[1]);
  f.denominator = atoll(argv[2]);

  Division d = Division(f);
  try {
    DivisionResult r = d.divide();

    std::cout << "Division : " << f.numerator << " / " << f.denominator << " = " << r.division << "\n";
    std::cout << "Remainder: " << f.numerator << " % " << f.denominator << " = " << r.remainder << "\n";
  } catch (const asdf::error& ex) {
    if (ex.code() == 2)
    std::cout << "Can not divide by zero, Homer. Sober up!\n";
  }
  std::cout << std::endl;
  return 0;
}
