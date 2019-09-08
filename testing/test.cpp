#include <iostream>
#include <string>
#include <cstdlib>

#include "JsonValue.hpp"
#include "JsonValueTestFunctions.hpp"
#include "TestPrinterFunctions.hpp"

int main(void) {
  JsonValue jVal(JsonType::JFLOAT);

  printTestGroup("Bool values", testBool, jVal);
  printTestGroup("Float values", testFloat, jVal);
  printTestGroup("Int values", testInt, jVal);
  printTestGroup("String values", testString, jVal);
  printTestGroup("Array values", testArray, jVal);
  printTestGroup("Object values", testObject, jVal);

  return 0;
}
