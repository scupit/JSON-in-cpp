#include <iostream>
#include <string>
#include <cstdlib>

#include "JsonValue.hpp"
#include "JsonValueTestFunctions.hpp"
#include "ArithmeticTestFunctions.hpp"
#include "OperatorTestFunctions.hpp"
#include "TestPrinterFunctions.hpp"

#include <vector>

bool flagPassed(const unsigned int, const char**, const std::string&);
void testAll(const bool, const std::vector<void (*)(const bool)>&);
void testArithmeticOperators(const bool);
void testOperators(const bool);
void testValues(const bool);

int main(int argc, const char** argv) {
  testAll(argc == 1, {
    testOperators,
    testValues
  });

  testArithmeticOperators(flagPassed(argc, argv, "-a"));
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

void testArithmeticOperators(const bool shouldTestArithmeticOperators) {
  if (shouldTestArithmeticOperators) {
    printTestGroup("Addition operators", testAdditionOperators);
    printTestGroup("Subtraction operators", testSubtractionOperators);
    printTestGroup("Multiplication operators", testMultiplicationOperators);
    printTestGroup("Division operators", testDivisionOperators);
  }
}

void testAll(const bool shouldTestAll, const std::vector<void (*)(const bool)>& testFunctions) {
  if (shouldTestAll) {
    for (auto func : testFunctions) {
      func(true);
    }
  }
}

void testOperators(const bool shouldTestOperators) {
  if (shouldTestOperators) {
    printTestGroup("'=' operator", testEqualsOperators);
    printTestGroup("'==' and '!=' operators", testBoolEqualityOperators);
    printTestGroup("Comparison operators", testComparisonOperators);
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
