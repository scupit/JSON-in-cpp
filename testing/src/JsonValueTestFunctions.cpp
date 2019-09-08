#include "TestPrinterFunctions.hpp"

#include <stdexcept>

void testFloat(JsonValue& jVal) {
  const float expectedFloatValue = 10.2f;
  jVal.setValue(expectedFloatValue);

  printTestResultStatus(
    "Float value assignment",
    *static_cast<float*>(jVal.getValue()) == expectedFloatValue
  );

  printTestResultStatus(
    "Expected JFLOAT type",
    jVal.getType() == JsonType::JFLOAT
  );

  jVal.changeType(JsonType::JFLOAT);

  printTestResultStatus(
    "Changing type from JFLOAT to JFLOAT",
    *static_cast<float*>(jVal.getValue()) == expectedFloatValue && jVal.getType() == JsonType::JFLOAT
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
    *static_cast<float*>(jVal.getValue()) == 0.0f
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JFLOAT to JSTRING",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JFLOAT);

  printTestResultStatus(
    "Changing back to JFLOAT from JSTRING",
    jVal.getType() == JsonType::JFLOAT && *static_cast<float*>(jVal.getValue()) == 0.0f
  );
}

void testInt(JsonValue& jVal) {
  const int expectedIntValue = -123;
  jVal.setValue(expectedIntValue);

  printTestResultStatus(
    "Int value assignment",
    *static_cast<int*>(jVal.getValue()) == expectedIntValue
  );

  printTestResultStatus(
    "Expected JINT type",
    jVal.getType() == JsonType::JINT
  );

  jVal.changeType(JsonType::JINT);

  printTestResultStatus(
    "Changing type from JINT to JINT",
    *static_cast<int*>(jVal.getValue()) == expectedIntValue && jVal.getType() == JsonType::JINT
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
    *static_cast<int*>(jVal.getValue()) == 0
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JINT to JSTRING",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JINT);

  printTestResultStatus(
    "Changing back to JINT from JSTRING",
    jVal.getType() == JsonType::JINT && *static_cast<int*>(jVal.getValue()) == 0
  );
}
  
void testString(JsonValue& jVal) {
  const std::string expectedStringValue = "Very noice test string";
  jVal.setValue(expectedStringValue);

  printTestResultStatus(
    "String value assignment",
    *static_cast<std::string*>(jVal.getValue()) == expectedStringValue
  );

  printTestResultStatus(
    "Expected JSTRING type",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JSTRING to JSTRING",
    *static_cast<std::string*>(jVal.getValue()) == expectedStringValue && jVal.getType() == JsonType::JSTRING
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
    static_cast<std::string*>(jVal.getValue()) == nullptr
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing type from JSTRING to JSTRING",
    jVal.getType() == JsonType::JSTRING
  );

  jVal.changeType(JsonType::JSTRING);

  printTestResultStatus(
    "Changing back to JSTRING from JSTRING",
    jVal.getType() == JsonType::JSTRING && static_cast<std::string*>(jVal.getValue()) == nullptr
  );
}

void testArray(JsonValue& jVal) {
  jVal.changeType(JsonType::JARRAY);

  printTestResultStatus(
    "Changing to JARRAY type",
    jVal.getType() == JsonType::JARRAY
  );

  static_cast<JsonArray*>(jVal.getValue())->emplace_back(10);
  static_cast<JsonArray*>(jVal.getValue())->emplace_back(10.2f);

  printTestResultStatus(
    "Adding two JsonValues to the array (array size)",
    static_cast<JsonArray*>(jVal.getValue())->size() == 2
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (JARRAY type)",
    jVal.getType() == JsonType::JARRAY
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (item 1 type)",
    static_cast<JsonArray*>(jVal.getValue())->at(0).getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (item 1 type)",
    *static_cast<int*>(static_cast<JsonArray*>(jVal.getValue())->at(0).getValue()) == 10
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (item 2 type)",
    static_cast<JsonArray*>(jVal.getValue())->at(1).getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding two JsonValues to the array (item 2 value)",
    *static_cast<float*>(static_cast<JsonArray*>(jVal.getValue())->at(1).getValue()) == 10.2f
  );

  jVal.changeType(JsonType::JARRAY);

  printTestResultStatus(
    "Changing type from JARRAY to JARRAY (correct length)",
    static_cast<JsonArray*>(jVal.getValue())->size() == 2
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
    static_cast<JsonArray*>(jVal.getValue())->empty()
  );

  jVal.changeType(JsonType::JARRAY);

  printTestResultStatus(
    "Changing type from JARRAY to JARRAY",
    jVal.getType() == JsonType::JARRAY
  );

  jVal.changeType(JsonType::JARRAY);

  printTestResultStatus(
    "Changing back to JARRAY from JARRAY",
    jVal.getType() == JsonType::JARRAY && static_cast<JsonArray*>(jVal.getValue())->empty()
  );
}

void testObject(JsonValue& jVal) {
  jVal.changeType(JsonType::JOBJECT);

  printTestResultStatus(
    "Changing to JOBJECT type",
    jVal.getType() == JsonType::JOBJECT
  );

  (*static_cast<JsonObject*>(jVal.getValue()))["theInt"] = JsonValue(10);
  (*static_cast<JsonObject*>(jVal.getValue()))["theFloat"] = JsonValue(10.2f);

  printTestResultStatus(
    "Adding two JsonValues to the map (size)",
    static_cast<JsonObject*>(jVal.getValue())->size() == 2
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (JOBJECT type)",
    jVal.getType() == JsonType::JOBJECT
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (item 1 type)",
    static_cast<JsonObject*>(jVal.getValue())->at("theInt").getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (item 1 value)",
    *static_cast<int*>(static_cast<JsonObject*>(jVal.getValue())->at("theInt").getValue()) == 10
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (item 2 type)",
    static_cast<JsonObject*>(jVal.getValue())->at("theFloat").getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding two JsonValues to the map (item 2 value)",
    *static_cast<float*>(static_cast<JsonObject*>(jVal.getValue())->at("theFloat").getValue()) == 10.2f
  );

  jVal.changeType(JsonType::JOBJECT);

  printTestResultStatus(
    "Changing type from JOBJECT to JOBJECT (correct size)",
    static_cast<JsonObject*>(jVal.getValue())->size() == 2
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
    static_cast<JsonObject*>(jVal.getValue())->empty()
  );

  jVal.changeType(JsonType::JOBJECT);

  printTestResultStatus(
    "Changing type from JOBJECT to JOBJECT",
    jVal.getType() == JsonType::JOBJECT
  );

  jVal.changeType(JsonType::JOBJECT);

  printTestResultStatus(
    "Changing back to JOBJECT from JOBJECT",
    jVal.getType() == JsonType::JOBJECT && static_cast<JsonObject*>(jVal.getValue())->empty()
  );
}
