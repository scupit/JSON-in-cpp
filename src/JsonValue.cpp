#include "JsonValue.hpp"

#include <stdexcept>

JsonValue::JsonValue(const std::nullptr_t nullType)
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

JsonValue::JsonValue(const char* newStringValue)
: type(JsonType::JSTRING), value({})
{
  value.stringValue = new std::string(newStringValue);
}

JsonValue::JsonValue(const std::string& newStringValue)
: type(JsonType::JSTRING), value({})
{
  value.stringValue = new std::string(newStringValue);
}

JsonValue::JsonValue(const JsonArray& newArrayValue)
: type(JsonType::JARRAY), value({})
{
  value.arrayValue = new JsonArray(newArrayValue);
}

JsonValue::JsonValue(const JsonObject& newObjectValue)
: type(JsonType::JOBJECT), value({})
{
  value.objectValue = new JsonObject(newObjectValue);
}

JsonValue::JsonValue(const JsonValue& other)
: type(other.type), value({})
{
  switch (other.type) {
    case JsonType::JSTRING:
      value.stringValue = new std::string(*other.value.stringValue);
      break;
    case JsonType::JARRAY:
      value.arrayValue = new JsonArray(*other.value.arrayValue);
      break;
    case JsonType::JOBJECT:
      value.objectValue = new JsonObject(*other.value.objectValue);
      break;
    default:
      value = other.value;
      break;
  }
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

void JsonValue::setNull(void) {
  if (type != JsonType::JNULL) {
    destroyCurrentValue();
  }
  type = JsonType::JNULL;
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

void JsonValue::setValue(const char* newStringValue) {
  if (type != JsonType::JSTRING) {
    destroyCurrentValue();
    value.stringValue = new std::string(newStringValue);
  }

  *value.stringValue = newStringValue;
  type = JsonType::JSTRING;
}

void JsonValue::setValue(const std::string& newStringValue) {
  if (type != JsonType::JSTRING) {
    destroyCurrentValue();
    value.stringValue = new std::string(newStringValue);
  }

  *value.stringValue = newStringValue;
  type = JsonType::JSTRING;
}

void JsonValue::setValue(const JsonArray& newArrayValue) {
  if (type != JsonType::JARRAY) {
    destroyCurrentValue();
    value.arrayValue = new JsonArray(newArrayValue);
  }
  *value.arrayValue = newArrayValue;
  type = JsonType::JARRAY;
}

void JsonValue::setValue(const JsonObject& newObjectValue) {
  if (type != JsonType::JOBJECT) {
    destroyCurrentValue();
    value.objectValue = new JsonObject(newObjectValue);
  }
  *value.objectValue = newObjectValue;
  type = JsonType::JOBJECT;
}

std::nullptr_t JsonValue::getAsNull() {
  if (type != JsonType::JNULL) {
    throw std::runtime_error("Tried to get JsonValue value as null (nullptr), when it it not of type JNULL");
  }
  return nullptr;
}

int JsonValue::getAsInt() {
  if (type != JsonType::JINT) {
    throw std::runtime_error("Tried to get JsonValue value as int, when it is not type JINT");
  }
  return value.intValue;
}

float JsonValue::getAsFloat() {
  if (type != JsonType::JFLOAT) {
    throw std::runtime_error("Tried to get JsonValue value as float, when it is not type JFLOAT");
  }
  return value.floatValue;
}

bool JsonValue::getAsBool() {
  if (type != JsonType::JBOOL) {
    throw std::runtime_error("Tried to get JsonValue value as bool, when it is not type JBOOL");
  }
  return value.boolValue;
}

std::string& JsonValue::getAsString() {
  if (type != JsonType::JSTRING) {
    throw std::runtime_error("Tried to get JsonValue value as std::string, when it is not type JSTRING.");
  }
  return *value.stringValue;
}

JsonArray& JsonValue::getAsVector() {
  if (type != JsonType::JARRAY) {
    throw std::runtime_error("Tried to get JsonValue value as JsonArray (std::vector), when it is not type JARRAY.");
  }
  return *value.arrayValue;
}

JsonObject& JsonValue::getAsMap() {
  if (type != JsonType::JOBJECT) {
    throw std::runtime_error("Tried to get JsonValue value as JsonObject (std::unordered_map), when it is not type JOBJECT.");
  }
  return *value.objectValue;
}

bool JsonValue::typeMatches(const JsonValue& other) const {
  return type == other.type;
}

JsonValue& JsonValue::operator=(const JsonValue& other) {
  switch (other.type) {
    case JsonType::JSTRING:
      setValue(*other.value.stringValue);
      break;
    case JsonType::JARRAY:
      setValue(*other.value.arrayValue);
      break;
    case JsonType::JOBJECT:
      setValue(*other.value.objectValue);
      break;
    case JsonType::JINT:
      setValue(other.value.intValue);
      break;
    case JsonType::JFLOAT:
      setValue(other.value.floatValue);
      break;
    case JsonType::JBOOL:
      setValue(other.value.boolValue);
      break;
    default:
      type = other.type;
      break;
  }
  return *this;
}

int JsonValue::operator=(const int newIntValue) {
  setValue(newIntValue);
  return newIntValue;
}

float JsonValue::operator=(const float newFloatValue) {
  setValue(newFloatValue);
  return newFloatValue;
}

const char* JsonValue::operator=(const char* newStringValue) {
  setValue(newStringValue);
  return newStringValue;
}

bool JsonValue::operator=(const bool newBoolValue) {
  setValue(newBoolValue);
  return newBoolValue;
}

std::string& JsonValue::operator=(std::string& newStringValue) {
  setValue(newStringValue);
  return newStringValue;
}

const JsonArray& JsonValue::operator=(const JsonArray& newArrayValue) {
  setValue(newArrayValue);
  return newArrayValue;
}

const JsonObject& JsonValue::operator=(const JsonObject& newObjectValue) {
  setValue(newObjectValue);
  return newObjectValue;
}

bool JsonValue::operator==(const JsonValue& other) {
  if (!typeMatches(other)) {
    return false;
  }
  
  switch (other.type) {
    case JsonType::JSTRING:
      return *this == other.value.stringValue;
    case JsonType::JARRAY:
      return *this == other.value.arrayValue;
    case JsonType::JOBJECT:
      return *this == other.value.objectValue;
    case JsonType::JINT:
      return *this == other.value.intValue;
    case JsonType::JFLOAT:
      return *this == other.value.floatValue;
    case JsonType::JBOOL:
      return *this == other.value.boolValue;
    default:
      return true;
  }
}

bool JsonValue::operator==(const int otherIntValue) {
  if (type != JsonType::JINT) {
    throw std::runtime_error("Attempted to check if an int is equal to a JsonValue not of type JINT");
  }
  return value.intValue == otherIntValue;
}

bool JsonValue::operator==(const float otherFloatValue) {
  if (type != JsonType::JFLOAT) {
    throw std::runtime_error("Attempted to check if a float is equal to a JsonValue not of type JFLOAT");
  }
  return value.floatValue == otherFloatValue;
}

bool JsonValue::operator==(const bool otherBoolValue) {
  if (type != JsonType::JBOOL) {
    throw std::runtime_error("Attempted to check if a bool id equal to a JsonValue not of type JBOOL");
  }
  return value.boolValue = otherBoolValue;
}

bool JsonValue::operator==(const char* otherStringValue) {
  if (type != JsonType::JSTRING) {
    throw std::runtime_error("Attempted to check if a const char* is equal to a JsonValue not of type JSTRING");
  }
  return (*value.stringValue) == otherStringValue;
}

bool JsonValue::operator==(const std::string& otherStringValue) {
  if (type != JsonType::JSTRING) {
    throw std::runtime_error("Attempted to check if an std::string is equal to a JsonValue not of type JSTRING");
  }
  return (*value.stringValue) == otherStringValue;
}

bool JsonValue::operator==(const JsonArray& otherArrayValue) {
  if (type != JsonType::JARRAY) {
    throw std::runtime_error("Attempted to check if JsonArray (std::vector) is equal to a JsonValue not of type JARRAY");
  }

  if (value.arrayValue->size() != otherArrayValue.size()) {
    return false;
  }
  
  for (unsigned int i = 0; i < otherArrayValue.size(); ++i) {
    if ( (*value.arrayValue)[i] != otherArrayValue) {
      return false;
    }
  }
  return true;
}

bool JsonValue::operator==(const JsonObject& otherObjectValue) {
  if (type != JsonType::JOBJECT) {
    throw std::runtime_error("Attempted to check if JsonObject (std::unordered_map) is equal to a JsonValue not of type JOBJECT");
  }

  if (value.objectValue->size() != otherObjectValue.size()) {
    return false;
  }

  for (auto iter = value.objectValue->begin(); iter != value.objectValue->end(); ++iter) {
    const auto search = otherObjectValue.find(iter->first);
    if (search == otherObjectValue.end() || search->second != iter->second) {
      return false;
    }
  }
  return true;
}

bool JsonValue::operator!=(const JsonValue& other) {
  return !(*this == other);
}

bool JsonValue::operator!=(const int otherIntValue) {
  return !(*this == otherIntValue);
}

bool JsonValue::operator!=(const float otherFloatValue) {
  return !(*this == otherFloatValue);
}

bool JsonValue::operator!=(const bool otherBoolValue) {
  return !(*this == otherBoolValue);
}

bool JsonValue::operator!=(const char* otherStringValue) {
  return !(*this == otherStringValue);
}

bool JsonValue::operator!=(const std::string& otherStringValue) {
  return !(*this == otherStringValue);
}

bool JsonValue::operator!=(const JsonArray& otherArrayValue) {
  return !(*this == otherArrayValue);
}

bool JsonValue::operator!=(const JsonObject& otherObjectValue) {
  return !(*this == otherObjectValue);
}

JsonValue& JsonValue::operator[](const int index) {
  if (type != JsonType::JARRAY) {
    throw std::runtime_error("Attemped to use array operator on JsonValue not of type JARRAY");
  }
  return value.arrayValue->at(index);
}

JsonValue& JsonValue::operator[](const std::string& key) {
  if (type != JsonType::JOBJECT) {
    throw std::runtime_error("Attemped to access a map key on JsonValue not of type JOBJECT");
  }
  auto valIter = value.objectValue->find(key);

  if (valIter == value.objectValue->end()) {
    (*value.objectValue)[key] = JsonValue();
    return value.objectValue->at("key");
  }
  else {
    return valIter->second;
  }
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
      value.boolValue = false;
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
