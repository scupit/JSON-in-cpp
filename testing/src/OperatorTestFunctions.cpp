#include "OperatorTestFunctions.hpp"
#include "TestPrinterFunctions.hpp"

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