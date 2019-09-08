#include "TestPrinterFunctions.hpp"

#include <stdexcept>

void testBool(JsonValue& jVal) {
  const bool expectedBoolValue = true;
  jVal.setValue(expectedBoolValue);

  printTestResultStatus(
    "Bool value assignment",
    jVal.getAsBool() == expectedBoolValue
  );

  printTestResultStatus(
    "Expected JBOOL type",
    jVal.getType() == JsonType::JBOOL
  );

  jVal.changeType(JsonType::JBOOL);

  printTestResultStatus(
    "Changing type from JBOOL to JBOOL",
    jVal.getAsBool() == expectedBoolValue && jVal.getType() == JsonType::JBOOL
  );

  printTestResultStatus(
    "Getting value using bool getter",
    jVal.getAsBool() == expectedBoolValue
  );

  try {
    int temp = jVal.getAsInt();
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

  jVal.resetValue();

  printTestResultStatus(
    "Resetting bool value",
    jVal.getAsBool() == false
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JBOOL to JSTRING",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JBOOL);

  printTestResultStatus(
    "Changing back to JBOOL from JSTRING",
    jVal.getType() == JsonType::JBOOL && jVal.getAsBool() == false
  );
}

void testFloat(JsonValue& jVal) {
  const float expectedFloatValue = 10.2f;
  jVal.setValue(expectedFloatValue);

  printTestResultStatus(
    "Float value assignment",
    jVal.getAsFloat() == expectedFloatValue
  );

  printTestResultStatus(
    "Expected JFLOAT type",
    jVal.getType() == JsonType::JFLOAT
  );

  jVal.changeType(JsonType::JFLOAT);

  printTestResultStatus(
    "Changing type from JFLOAT to JFLOAT",
    jVal.getAsFloat() == expectedFloatValue && jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Getting value using float getter",
    jVal.getAsFloat() == expectedFloatValue
  );

  try {
    int temp = jVal.getAsInt();
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

  jVal.resetValue();

  printTestResultStatus(
    "Resetting float value",
    jVal.getAsFloat() == 0.0f
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JFLOAT to JSTRING",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JFLOAT);

  printTestResultStatus(
    "Changing back to JFLOAT from JSTRING",
    jVal.getType() == JsonType::JFLOAT && jVal.getAsFloat() == 0.0f
  );
}

void testInt(JsonValue& jVal) {
  const int expectedIntValue = -123;
  jVal.setValue(expectedIntValue);

  printTestResultStatus(
    "Int value assignment",
    jVal.getAsInt() == expectedIntValue
  );

  printTestResultStatus(
    "Expected JINT type",
    jVal.getType() == JsonType::JINT
  );

  jVal.changeType(JsonType::JINT);

  printTestResultStatus(
    "Changing type from JINT to JINT",
    jVal.getAsInt() == expectedIntValue && jVal.getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Getting value using int getter",
    jVal.getAsInt() == expectedIntValue
  );

  try {
    std::string& temp = jVal.getAsString();
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

  jVal.resetValue();

  printTestResultStatus(
    "Resetting int value",
    jVal.getAsInt() == 0
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JINT to JSTRING",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JINT);

  printTestResultStatus(
    "Changing back to JINT from JSTRING",
    jVal.getType() == JsonType::JINT && jVal.getAsInt() == 0
  );
}
  
void testString(JsonValue& jVal) {
  const std::string expectedStringValue = "Very noice test string";
  jVal.setValue(expectedStringValue);

  printTestResultStatus(
    "String value assignment",
    jVal.getAsString() == expectedStringValue
  );

  printTestResultStatus(
    "Expected JSTRING type",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JSTRING to JSTRING",
    jVal.getAsString() == expectedStringValue && jVal.getType() == JsonType::JSTRING
  );

  printTestResultStatus(
    "Getting value using std::string getter",
    jVal.getAsString() == expectedStringValue
  );

  try {
    JsonArray& temp = jVal.getAsVector();
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

  jVal.resetValue();

  printTestResultStatus(
    "Resetting string value",
    jVal.getAsString() == ""
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JSTRING to JSTRING",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing back to JSTRING from JSTRING",
    jVal.getType() == JsonType::JSTRING && jVal.getAsString() == ""
  );
}

void testArray(JsonValue& jVal) {
  jVal.changeType(JsonType::JARRAY);

  printTestResultStatus(
    "Changing to JARRAY type",
    jVal.getType() == JsonType::JARRAY
  );

  jVal.getAsVector().emplace_back(10);
  jVal.getAsVector().emplace_back(10.2f);

  printTestResultStatus(
    "Adding two JsonValues to the array (array size)",
    jVal.getAsVector().size() == 2
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (JARRAY type)",
    jVal.getType() == JsonType::JARRAY
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (item 1 type)",
    jVal.getAsVector().at(0).getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (item 1 type)",
    jVal.getAsVector().at(0).getAsInt() == 10
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (item 2 type)",
    jVal.getAsVector().at(1).getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (item 2 value)",
    jVal.getAsVector().at(1).getAsFloat() == 10.2f
  );

  jVal.changeType(JsonType::JARRAY);

  printTestResultStatus(
    "Changing type from JARRAY to JARRAY (correct length)",
    jVal.getAsVector().size() == 2
  );

  printTestResultStatus(
    "Changing type from JARRAY to JARRAY (is JARRAY type)",
    jVal.getType() == JsonType::JARRAY
  );

  printTestResultStatus(
    "Getting value using JsonArray getter",
    jVal.getAsVector().size() == 2
  );

  try {
    JsonObject& temp = jVal.getAsMap();
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

  jVal.resetValue();

  printTestResultStatus(
    "Resetting int value",
    jVal.getAsVector().empty()
  );

  jVal.changeType(JsonType::JARRAY);

  printTestResultStatus(
    "Changing type from JARRAY to JARRAY",
    jVal.getType() == JsonType::JARRAY
  );

  jVal.changeType(JsonType::JARRAY);

  printTestResultStatus(
    "Changing back to JARRAY from JARRAY",
    jVal.getType() == JsonType::JARRAY && jVal.getAsVector().empty()
  );
}

void testObject(JsonValue& jVal) {
  jVal.changeType(JsonType::JOBJECT);

  printTestResultStatus(
    "Changing to JOBJECT type",
    jVal.getType() == JsonType::JOBJECT
  );

  jVal.getAsMap()["theInt"] = JsonValue(10);
  jVal.getAsMap()["theFloat"] = JsonValue(10.2f);

  printTestResultStatus(
    "Adding two JsonValues to the map (size)",
    jVal.getAsMap().size() == 2
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (JOBJECT type)",
    jVal.getType() == JsonType::JOBJECT
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (item 1 type)",
    jVal.getAsMap().at("theInt").getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (item 1 value)",
    jVal.getAsMap().at("theInt").getAsInt() == 10
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (item 2 type)",
    jVal.getAsMap().at("theFloat").getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (item 2 value)",
    jVal.getAsMap().at("theFloat").getAsFloat() == 10.2f
  );

  jVal.changeType(JsonType::JOBJECT);

  printTestResultStatus(
    "Changing type from JOBJECT to JOBJECT (correct size)",
    jVal.getAsMap().size() == 2
  );

  printTestResultStatus(
    "Changing type from JOBJECT to JOBJECT (JOBJECT type)",
    jVal.getType() == JsonType::JOBJECT
  );

  printTestResultStatus(
    "Getting value using JsonArray getter",
    jVal.getAsMap().size() == 2
  );

  try {
    float temp = jVal.getAsFloat();
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

  jVal.resetValue();

  printTestResultStatus(
    "Resetting int value",
    jVal.getAsMap().empty()
  );

  jVal.changeType(JsonType::JOBJECT);

  printTestResultStatus(
    "Changing type from JOBJECT to JOBJECT",
    jVal.getType() == JsonType::JOBJECT
  );

  jVal.changeType(JsonType::JOBJECT);

  printTestResultStatus(
    "Changing back to JOBJECT from JOBJECT",
    jVal.getType() == JsonType::JOBJECT && jVal.getAsMap().empty()
  );
}
