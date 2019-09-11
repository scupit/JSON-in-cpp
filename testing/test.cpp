#include <iostream>
#include <string>
#include <cstdlib>

#include "JsonValue.hpp"
#include "JsonValueTestFunctions.hpp"
#include "OperatorTestFunctions.hpp"
#include "TestPrinterFunctions.hpp"

bool flagPassed(const unsigned int, const char**, const std::string&);
void testOperators(const bool);
void testValues(const bool);

int main(int argc, const char** argv) {
  testOperators(flagPassed(argc, argv, "-o"));
  testValues(flagPassed(argc, argv, "-v"));
  return 0;
}

bool flagPassed(const unsigned int argc, const char** argv, const std::string& flag) {
  for (unsigned int i = 0; i < argc; ++i) {
    if (argv[i] == flag) {
      return true;
    }
  }
  return false;
}

void testOperators(const bool shouldTestOperators) {
  if (shouldTestOperators) {
    printTestGroup("'=' operator", testEqualsOperators);
    printTestGroup("'==' and '!=' operators", testBoolEqualityOperators);
  }
}

void testValues(const bool shouldTestValues) {
  if (shouldTestValues) {
    printTestGroup("Bool values", testBool);
    printTestGroup("Float values", testFloat);
    printTestGroup("Int values", testInt);
    printTestGroup("String values", testString);
    printTestGroup("Array values", testArray);
    printTestGroup("Object values", testObject);
  }
}
