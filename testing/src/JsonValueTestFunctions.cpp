#include "TestPrinterFunctions.hpp"

#include <stdexcept>

void testBool(JsonValue& jVal) {
  const bool expectedBoolValue = true;
  jVal.set(expectedBoolValue);

  printTestResultStatus(
    "Bool value assignment",
    jVal.asBool() == expectedBoolValue
  );

  printTestResultStatus(
    "Expected JBOOL type",
    jVal.getType() == JsonType::JBOOL
  );

  jVal.changeType(JsonType::JBOOL);

  printTestResultStatus(
    "Changing type from JBOOL to JBOOL",
    jVal.asBool() == expectedBoolValue && jVal.getType() == JsonType::JBOOL
  );

  printTestResultStatus(
    "Getting value using bool getter",
    jVal.asBool() == expectedBoolValue
  );

  try {
    int temp = jVal.asInt();
    printTestResultStatus(
      "Using getter of wrong type",
      false
    );
  }
  catch (std::runtime_error& e) {
    printTestResultStatus(
      "Using getter of wrong type",
      true
    );
  }

  jVal.reset();

  printTestResultStatus(
    "Resetting bool value",
    jVal.asBool() == false
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JBOOL to JSTRING",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JBOOL);

  printTestResultStatus(
    "Changing back to JBOOL from JSTRING",
    jVal.getType() == JsonType::JBOOL && jVal.asBool() == false
  );
}

void testFloat(JsonValue& jVal) {
  const float expectedFloatValue = 10.2f;
  jVal.set(expectedFloatValue);

  printTestResultStatus(
    "Float value assignment",
    jVal.asFloat() == expectedFloatValue
  );

  printTestResultStatus(
    "Expected JFLOAT type",
    jVal.getType() == JsonType::JFLOAT
  );

  jVal.changeType(JsonType::JFLOAT);

  printTestResultStatus(
    "Changing type from JFLOAT to JFLOAT",
    jVal.asFloat() == expectedFloatValue && jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Getting value using float getter",
    jVal.asFloat() == expectedFloatValue
  );

  try {
    int temp = jVal.asInt();
    printTestResultStatus(
      "Using getter of wrong type",
      false
    );
  }
  catch (std::runtime_error& e) {
    printTestResultStatus(
      "Using getter of wrong type",
      true
    );
  }

  jVal.reset();

  printTestResultStatus(
    "Resetting float value",
    jVal.asFloat() == 0.0f
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JFLOAT to JSTRING",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JFLOAT);

  printTestResultStatus(
    "Changing back to JFLOAT from JSTRING",
    jVal.getType() == JsonType::JFLOAT && jVal.asFloat() == 0.0f
  );
}

void testInt(JsonValue& jVal) {
  const int expectedIntValue = -123;
  jVal.set(expectedIntValue);

  printTestResultStatus(
    "Int value assignment",
    jVal.asInt() == expectedIntValue
  );

  printTestResultStatus(
    "Expected JINT type",
    jVal.getType() == JsonType::JINT
  );

  jVal.changeType(JsonType::JINT);

  printTestResultStatus(
    "Changing type from JINT to JINT",
    jVal.asInt() == expectedIntValue && jVal.getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Getting value using int getter",
    jVal.asInt() == expectedIntValue
  );

  try {
    std::string& temp = jVal.asString();
    printTestResultStatus(
      "Using getter of wrong type",
      false
    );
  }
  catch (std::runtime_error& e) {
    printTestResultStatus(
      "Using getter of wrong type",
      true
    );
  }

  jVal.reset();

  printTestResultStatus(
    "Resetting int value",
    jVal.asInt() == 0
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JINT to JSTRING",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JINT);

  printTestResultStatus(
    "Changing back to JINT from JSTRING",
    jVal.getType() == JsonType::JINT && jVal.asInt() == 0
  );
}
  
void testString(JsonValue& jVal) {
  const std::string expectedStringValue = "Very noice test string";
  jVal.set(expectedStringValue);

  printTestResultStatus(
    "String value assignment",
    jVal.asString() == expectedStringValue
  );

  printTestResultStatus(
    "Expected JSTRING type",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JSTRING to JSTRING",
    jVal.asString() == expectedStringValue && jVal.getType() == JsonType::JSTRING
  );

  printTestResultStatus(
    "Getting value using std::string getter",
    jVal.asString() == expectedStringValue
  );

  try {
    JsonArray& temp = jVal.asVector();
    printTestResultStatus(
      "Using getter of wrong type",
      false
    );
  }
  catch (std::runtime_error& e) {
    printTestResultStatus(
      "Using getter of wrong type",
      true
    );
  }

  jVal.reset();

  printTestResultStatus(
    "Resetting string value",
    jVal.asString() == ""
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JSTRING to JSTRING",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing back to JSTRING from JSTRING",
    jVal.getType() == JsonType::JSTRING && jVal.asString() == ""
  );
}

void testArray(JsonValue& jVal) {
  jVal.changeType(JsonType::JARRAY);

  printTestResultStatus(
    "Changing to JARRAY type",
    jVal.getType() == JsonType::JARRAY
  );

  jVal.asVector().emplace_back(10);
  jVal.asVector().emplace_back(10.2f);

  printTestResultStatus(
    "Adding two JsonValues to the array (array size)",
    jVal.asVector().size() == 2
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (JARRAY type)",
    jVal.getType() == JsonType::JARRAY
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (item 1 type)",
    jVal.asVector().at(0).getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (item 1 type)",
    jVal.asVector().at(0).asInt() == 10
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (item 2 type)",
    jVal.asVector().at(1).getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (item 2 value)",
    jVal.asVector().at(1).asFloat() == 10.2f
  );

  jVal.changeType(JsonType::JARRAY);

  printTestResultStatus(
    "Changing type from JARRAY to JARRAY (correct length)",
    jVal.asVector().size() == 2
  );

  printTestResultStatus(
    "Changing type from JARRAY to JARRAY (is JARRAY type)",
    jVal.getType() == JsonType::JARRAY
  );

  printTestResultStatus(
    "Getting value using JsonArray getter",
    jVal.asVector().size() == 2
  );

  try {
    JsonObject& temp = jVal.asMap();
    printTestResultStatus(
      "Using getter of wrong type",
      false
    );
  }
  catch (std::runtime_error& e) {
    printTestResultStatus(
      "Using getter of wrong type",
      true
    );
  }

  jVal.reset();

  printTestResultStatus(
    "Resetting int value",
    jVal.asVector().empty()
  );

  jVal.changeType(JsonType::JARRAY);

  printTestResultStatus(
    "Changing type from JARRAY to JARRAY",
    jVal.getType() == JsonType::JARRAY
  );

  jVal.changeType(JsonType::JARRAY);

  printTestResultStatus(
    "Changing back to JARRAY from JARRAY",
    jVal.getType() == JsonType::JARRAY && jVal.asVector().empty()
  );
}

void testObject(JsonValue& jVal) {
  jVal.changeType(JsonType::JOBJECT);

  printTestResultStatus(
    "Changing to JOBJECT type",
    jVal.getType() == JsonType::JOBJECT
  );

  jVal.asMap()["theInt"] = JsonValue(10);
  jVal.asMap()["theFloat"] = JsonValue(10.2f);

  printTestResultStatus(
    "Adding two JsonValues to the map (size)",
    jVal.asMap().size() == 2
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (JOBJECT type)",
    jVal.getType() == JsonType::JOBJECT
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (item 1 type)",
    jVal.asMap().at("theInt").getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (item 1 value)",
    jVal.asMap().at("theInt").asInt() == 10
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (item 2 type)",
    jVal.asMap().at("theFloat").getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (item 2 value)",
    jVal.asMap().at("theFloat").asFloat() == 10.2f
  );

  jVal.changeType(JsonType::JOBJECT);

  printTestResultStatus(
    "Changing type from JOBJECT to JOBJECT (correct size)",
    jVal.asMap().size() == 2
  );

  printTestResultStatus(
    "Changing type from JOBJECT to JOBJECT (JOBJECT type)",
    jVal.getType() == JsonType::JOBJECT
  );

  printTestResultStatus(
    "Getting value using JsonArray getter",
    jVal.asMap().size() == 2
  );

  try {
    float temp = jVal.asFloat();
    printTestResultStatus(
      "Using getter of wrong type",
      false
    );
  }
  catch (std::runtime_error& e) {
    printTestResultStatus(
      "Using getter of wrong type",
      true
    );
  }

  jVal.reset();

  printTestResultStatus(
    "Resetting int value",
    jVal.asMap().empty()
  );

  jVal.changeType(JsonType::JOBJECT);

  printTestResultStatus(
    "Changing type from JOBJECT to JOBJECT",
    jVal.getType() == JsonType::JOBJECT
  );

  jVal.changeType(JsonType::JOBJECT);

  printTestResultStatus(
    "Changing back to JOBJECT from JOBJECT",
    jVal.getType() == JsonType::JOBJECT && jVal.asMap().empty()
  );
}
