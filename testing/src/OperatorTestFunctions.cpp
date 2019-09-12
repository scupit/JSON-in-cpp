#include "OperatorTestFunctions.hpp"
#include "TestPrinterFunctions.hpp"

#include <iostream>

void testEqualsOperators(JsonValue& jVal) {
  jVal = JsonValue();

  printTestResultStatus(
    "Assigning to JsonValue()",
    jVal.getType() == JsonType::JNULL
  );

  jVal = -123;

  printTestResultStatus(
    "Assigning to int",
    jVal.getType() == JsonType::JINT
      && jVal.getAsInt() == -123
  );

  jVal = 10.2f;

  printTestResultStatus(
    "Assigning to float",
    jVal.getType() == JsonType::JFLOAT
      && jVal.getAsFloat() == 10.2f
  );

  jVal = "A noice string";

  printTestResultStatus(
    "Assigning to string",
    jVal.getType() == JsonType::JSTRING
      && jVal.getAsString() == "A noice string"
  );


  jVal = { 12, "good string", -109, 104.5f };

  printTestResultStatus(
    "Assigning to brace-initialized array (type check)",
    jVal.getType() == JsonType::JARRAY
  );

  printTestResultStatus(
    "Assigning to brace-initialized array (value check)",
    jVal[0].getAsInt() == 12
      && jVal[1].getAsString() == "good string"
      && jVal[2].getAsInt() == -109
      && jVal[3].getAsFloat() == 104.5f
  );

  jVal = {
    {"integer", -123},
    {"boolean", true},
    {"null", nullptr},
    {"string", "good string"},
    {"array", jVal.getAsVector()}
  };

  printTestResultStatus(
    "Assigning to brace-initialized map (type check)",
    jVal.getType() == JsonType::JOBJECT
  );

  printTestResultStatus(
    "Assigning to brace-initialized map (value check)",
    jVal["integer"].getAsInt() == -123
      && jVal["boolean"].getAsBool()
      && jVal["null"].getType() == JsonType::JNULL
      && jVal["string"].getAsString() == "good string"
      && jVal["array"][1].getAsString() == "good string"
      && jVal["array"][3].getAsFloat() == 104.5f 
  );

  jVal.setNull();

  printTestResultStatus(
    "Assigning to nullptr",
    jVal.getType() == JsonType::JNULL
  );
}

void testBoolEqualityOperators(JsonValue& jVal) {
  jVal = JsonValue("A nice string");

  printTestResultStatus(
    "String equality (const char*)",
    jVal == "A nice string"
  );

  printTestResultStatus(
    "String equality (const char*)",
    "A nice string" == jVal
  );

  printTestResultStatus(
    "String inequality (const char*)",
    jVal != "Some other nice string"
  );

  printTestResultStatus(
    "String inequality (const char*)",
    "Some other nice string" != jVal
  );

  printTestResultStatus(
    "String equality (std::string)",
    jVal == std::string("A nice string")
  );

  printTestResultStatus(
    "String equality (std::string)",
    std::string("A nice string") == jVal
  );

  printTestResultStatus(
    "String inequality (std::string)",
    jVal != std::string("Some other string")
  );

  printTestResultStatus(
    "String inequality (std::string)",
    std::string("Some other string") != jVal
  );

  jVal = -123;

  printTestResultStatus(
    "Int equality",
    jVal == -123
  );

  printTestResultStatus(
    "Int equality",
    -123 == jVal
  );

  printTestResultStatus(
    "Int inequality",
    jVal != 0
  );

  printTestResultStatus(
    "Int inequality",
    0 != jVal
  );

  jVal = true;

  printTestResultStatus(
    "Bool equality",
    jVal == true
  );

  printTestResultStatus(
    "Bool equality",
    true == jVal
  );

  printTestResultStatus(
    "Bool inequality",
    jVal != false
  );

  printTestResultStatus(
    "Bool inequality",
    false != jVal
  );

  jVal = 10.2f;

  printTestResultStatus(
    "Float equality",
    jVal == 10.2f
  );

  printTestResultStatus(
    "Float equality",
    10.2f == jVal
  );

  printTestResultStatus(
    "Float inequality",
    jVal != -123.4f
  );

  printTestResultStatus(
    "Float inequality",
    -123.4f != jVal
  );

  JsonArray arr = { 10.2f, "Something cool", JsonArray()};
  JsonArray otherArr = {10.2f, "Something cool", JsonArray({"Noice", "oh yeah"})};
  jVal = arr;

  // std::cout << (int)jVal.getType() << " should be " << (int)JsonType::JARRAY << std::endl;
  // std::cout << (int)arr[2].getType() << " should be " << (int)JsonType::JARRAY << std::endl;
  // std::cout << (int)otherArr[2].getType() << " should be " << (int)JsonType::JARRAY << std::endl;
  // std::cout << (int)otherArr[2][0].getType() << " should be " << (int)JsonType::JARRAY << std::endl;

  printTestResultStatus(
    "JsonArray (vector) equality",
    jVal == arr
  );

  printTestResultStatus(
    "JsonArray (vector) equality",
    arr == jVal
  );

  printTestResultStatus(
    "JsonArray (vector) inequality",
    jVal != otherArr
  );

  printTestResultStatus(
    "JsonArray (vector) inequality",
    otherArr != jVal
  );

  JsonObject aMap = {
    {"something", -123},
    {"another thing", "Noice"}
  };
  JsonObject otherMap = {
    {"something", -120},
    {"Another thing", "Noice"}
  };
  jVal = aMap;

  printTestResultStatus(
    "JsonObject (unordered_map) equality",
    jVal == aMap
  );

  printTestResultStatus(
    "JsonObject (unordered_map) equality",
    aMap == jVal
  );

  printTestResultStatus(
    "JsonObject (unordered_map) inequality",
    jVal != otherMap
  );

  printTestResultStatus(
    "JsonObject (unordered_map) inequality",
    otherMap != jVal
  );
}

void testComparisonOperators(JsonValue& jVal) {
  testLTOperator(jVal);
}

void testLTOperator(JsonValue& jVal) {
  jVal = 10.2f;

  printTestResultStatus(
    "'<' operator with float literal",
    !(jVal < 10.2f)
  );

  printTestResultStatus(
    "'<' operator with int literal",
    jVal < 11
  );

  printTestResultStatus(
    "'<' operator with JsonValue JFLOAT",
    jVal < JsonValue(10.4f)
  );

  printTestResultStatus(
    "'<' operator with JsonValue JINT",
    jVal < JsonValue(9)
  );

  printTestResultStatus(
    "'<' operator with float literal",
    !(jVal < 10.2f)
  );

  printTestResultStatus(
    "'<' operator with int literal",
    10 < jVal
  );

  printTestResultStatus(
    "'<' operator with JsonValue JFLOAT",
    JsonValue(1.4f) < jVal
  );

  printTestResultStatus(
    "'<' operator with JsonValue JINT",
    JsonValue(8) < jVal
  );
}