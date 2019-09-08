#include "JsonValue.hpp"

#include <stdexcept>

JsonValue::JsonValue()
: type(JsonType::JNULL), value({})
{ }

JsonValue::JsonValue(const JsonType type)
: type(type), value({})
{
  typeChangeHelper(type);
}

JsonValue::JsonValue(const int newIntValue)
: type(JsonType::JINT), value({newIntValue})
{ }

JsonValue::JsonValue(const float newFloatValue)
: type(JsonType::JFLOAT), value({})
{
  value.floatValue = newFloatValue;
}

JsonValue::JsonValue(const bool newBoolValue)
: type(JsonType::JBOOL), value({})
{
  value.boolValue = newBoolValue;
}

JsonValue::JsonValue(const std::string& newStringValue)
: type(JsonType::JSTRING), value({})
{
  value.stringValue = new std::string(newStringValue);
}

JsonValue::~JsonValue() {
  destroyCurrentValue();
}

void JsonValue::changeType(const JsonType newType) {
  if (type != newType) {
    destroyCurrentValue();
    type = newType;
    typeChangeHelper(newType);
  }
}

void JsonValue::resetValue() {
  destroyCurrentValue();
  typeChangeHelper(type);
}

void JsonValue::setValue(const int newIntValue) {
  if (type != JsonType::JINT) {
    destroyCurrentValue();
  }
  value.intValue = newIntValue;
  type = JsonType::JINT;
}

void JsonValue::setValue(const float newFloatValue) {
  if (type != JsonType::JFLOAT) {
    destroyCurrentValue();
  }
  value.floatValue = newFloatValue;
  type = JsonType::JFLOAT;
}

void JsonValue::setValue(const bool newBoolValue) {
  if (type != JsonType::JBOOL) {
    destroyCurrentValue();
  }
  value.boolValue = newBoolValue;
  type = JsonType::JBOOL;
}

void JsonValue::setValue(const std::string& newStringValue) {
  destroyCurrentValue();
  value.stringValue = new std::string(newStringValue);
  type = JsonType::JSTRING;
}

int JsonValue::getAsInt() {
  if (type != JsonType::JINT) {
    throw std::runtime_error("ERROR: Tried to get JsonValue value as int, when it is not type JINT");
  }
  return value.intValue;
}

float JsonValue::getAsFloat() {
  if (type != JsonType::JFLOAT) {
    throw std::runtime_error("ERROR: Tried to get JsonValue value as float, when it is not type JFLOAT");
  }
  return value.floatValue;
}

bool JsonValue::getAsBool() {
  if (type != JsonType::JFLOAT) {
    throw std::runtime_error("ERROR: Tried to get JsonValue value as bool, when it is not type JBOOL");
  }
  return value.boolValue;
}

std::string& JsonValue::getAsString() {
  if (type != JsonType::JSTRING) {
    throw std::runtime_error("ERROR: Tried to get JsonValue value as std::string, when it is not type JSTRING.");
  }
  return *value.stringValue;
}

JsonArray& JsonValue::getAsVector() {
  if (type != JsonType::JARRAY) {
    throw std::runtime_error("ERROR: Tried to get JsonValue value as JsonArray (std::vector), when it is not type JARRAY.");
  }
  return *value.arrayValue;
}

JsonObject& JsonValue::getAsMap() {
  if (type != JsonType::JOBJECT) {
    throw std::runtime_error("ERROR: Tried to get JsonValue value as JsonObject (std::unordered_map), when it is not type JOBJECT.");
  }
  return *value.objectValue;
}

// Only heap allocated values need to be destroyed.
void JsonValue::destroyCurrentValue() {
  switch (type) {
    case JsonType::JSTRING:
      delete value.stringValue;
      break;
    case JsonType::JOBJECT:
      delete value.objectValue;
      break;
    case JsonType::JARRAY:
      delete value.arrayValue;
      break;
    default:
      break;
  }
}

// Null and invalid types intentionally left out since null can be inferred from JsonType JNULL.
void JsonValue::typeChangeHelper(const JsonType newType) {
  switch (type) {
    case JsonType::JSTRING:
      value.stringValue = new std::string("");
      break;
    case JsonType::JOBJECT:
      value.objectValue = new JsonObject();
      break;
    case JsonType::JARRAY:
      value.arrayValue = new JsonArray();
      break;
    case JsonType::JBOOL:
      value.boolValue = true;
      break;
    case JsonType::JFLOAT:
      value.floatValue = 0.0f;
      break;
    case JsonType::JINT:
      value.intValue = 0;
      break;
    default:
      break;
  }
}
