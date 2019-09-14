#include "JsonValue.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
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

std::string JsonValue::stringify() {
  std::string str;
  stringify(str);
  return str;
}

void JsonValue::stringify(std::string& destinationString){
  std::stringstream strIn;
  stringifyHelper(strIn, 0);
  destinationString = strIn.str();
}

void JsonValue::stringify(std::ostream& out) {
  stringifyHelper(out, 0);
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

bool JsonValue::operator==(const JsonValue& other) const {
  if (!typeMatches(other)) {
    return false;
  }
  
  switch (other.type) {
    case JsonType::JSTRING:
      return *this == *other.value.stringValue;
    case JsonType::JARRAY:
      return *this == *other.value.arrayValue;
    case JsonType::JOBJECT:
      return *this == *other.value.objectValue;
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

bool JsonValue::operator==(const int otherIntValue) const {
  if (type == JsonType::JINT) {
    return value.intValue == otherIntValue;
  }
  else if (type == JsonType::JFLOAT) {
    return jfequal(value.floatValue, static_cast<float>(otherIntValue));
  }
  else {
    throw std::runtime_error("Attempted to check if an int is equal to a JsonValue not of type JINT or JFLOAT");
  }
}

bool JsonValue::operator==(const float otherFloatValue) const {
  if (type == JsonType::JFLOAT) {
    return jfequal(value.floatValue ,otherFloatValue);
  }
  else if (type == JsonType::JINT) {
    return jfequal(static_cast<float>(value.intValue) ,otherFloatValue);
  }
  else {
    throw std::runtime_error("Attempted to check if a float is equal to a JsonValue not of type JFLOAT or JINT");
  }
}

bool JsonValue::operator==(const bool otherBoolValue) const {
  if (type != JsonType::JBOOL) {
    throw std::runtime_error("Attempted to check if a bool id equal to a JsonValue not of type JBOOL");
  }
  return value.boolValue == otherBoolValue;
}

bool JsonValue::operator==(const char* otherStringValue) const {
  if (type != JsonType::JSTRING) {
    throw std::runtime_error("Attempted to check if a const char* is equal to a JsonValue not of type JSTRING");
  }
  return (*value.stringValue) == otherStringValue;
}

bool JsonValue::operator==(const std::string& otherStringValue) const {
  if (type != JsonType::JSTRING) {
    throw std::runtime_error("Attempted to check if an std::string is equal to a JsonValue not of type JSTRING");
  }
  return (*value.stringValue) == otherStringValue;
}

bool JsonValue::operator==(const JsonArray& otherArrayValue) const {
  if (type != JsonType::JARRAY) {
    throw std::runtime_error("Attempted to check if JsonArray (std::vector) is equal to a JsonValue not of type JARRAY");
  }
  return *value.arrayValue == otherArrayValue;
}

bool JsonValue::operator==(const JsonObject& otherObjectValue) const {
  if (type != JsonType::JOBJECT) {
    throw std::runtime_error("Attempted to check if JsonObject (std::unordered_map) is equal to a JsonValue not of type JOBJECT");
  }
  return *value.objectValue == otherObjectValue;
}

bool operator==(const int integer, const JsonValue& jVal)       { return jVal == integer; }
bool operator==(const float fp, const JsonValue& jVal)          { return jVal == fp;      }
bool operator==(const bool boolean, const JsonValue& jVal)      { return jVal == boolean; }
bool operator==(const std::string& str, const JsonValue& jVal)  { return jVal == str;     }
bool operator==(const char* str, const JsonValue& jVal)         { return jVal == str;     }
bool operator==(const JsonArray& arr, const JsonValue& jVal)    { return jVal == arr;     }
bool operator==(const JsonObject& obj, const JsonValue& jVal)   { return jVal == obj;     }

bool JsonValue::operator!=(const JsonValue& other) const {
  return !(*this == other);
}

bool JsonValue::operator!=(const int otherIntValue) const {
  return !(*this == otherIntValue);
}

bool JsonValue::operator!=(const float otherFloatValue) const {
  return !(*this == otherFloatValue);
}

bool JsonValue::operator!=(const bool otherBoolValue) const {
  return !(*this == otherBoolValue);
}

bool JsonValue::operator!=(const char* otherStringValue) const {
  return !(*this == otherStringValue);
}

bool JsonValue::operator!=(const std::string& otherStringValue) const {
  return !(*this == otherStringValue);
}

bool JsonValue::operator!=(const JsonArray& otherArrayValue) const {
  return !(*this == otherArrayValue);
}

bool JsonValue::operator!=(const JsonObject& otherObjectValue) const {
  return !(*this == otherObjectValue);
}

bool operator!=(const int integer, const JsonValue& jVal)       { return jVal != integer; }
bool operator!=(const float fp, const JsonValue& jVal)          { return jVal != fp;      }
bool operator!=(const bool boolean, const JsonValue& jVal)      { return jVal != boolean; }
bool operator!=(const char* str, const JsonValue& jVal)         { return jVal != str;     }
bool operator!=(const std::string& str, const JsonValue& jVal)  { return jVal != str;     }
bool operator!=(const JsonArray& arr, const JsonValue& jVal)    { return jVal != arr;     }
bool operator!=(const JsonObject& obj, const JsonValue& jVal)   { return jVal != obj;     }

bool JsonValue::operator<(const JsonValue& other) const {
  // If 'other' is valid type
  if (other.type == JsonType::JINT || other.type == JsonType::JFLOAT) {
    switch (type) {
      case JsonType::JINT:
        return other > value.intValue;
      case JsonType::JFLOAT:
        return other > value.floatValue;
      default:
        break;
    }
  }
  throw std::runtime_error("Tried to use the '<' operator on a non-numeric JsonValue");
}

bool JsonValue::operator<(const int integer) const {
  switch (type) {
    case JsonType::JINT:
      return value.intValue < integer;
    case JsonType::JFLOAT:
      return value.floatValue < static_cast<float>(integer);
    default:
      throw std::runtime_error("Tried to use the '<' operator on a non-numeric JsonValue");
  }
}

bool JsonValue::operator<(const float fp) const {
  switch (type) {
    case JsonType::JFLOAT:
      return value.floatValue < fp;
    case JsonType::JINT:
      return static_cast<float>(value.intValue) < fp;
    default:
      throw std::runtime_error("Tried to use the '<' operator on a non-numeric JsonValue");
  }
}

bool operator<(const int integer, const JsonValue& jVal) {
  return jVal > integer;
}

bool operator<(const float fp, const JsonValue& jVal) {
  return jVal > fp;
}

bool JsonValue::operator<=(const JsonValue& other) const {
  // If 'other' is valid type
  if (other.type == JsonType::JINT || other.type == JsonType::JFLOAT) {
    switch (type) {
      case JsonType::JINT:
        return other >= value.intValue;
      case JsonType::JFLOAT:
        return other >= value.floatValue;
      default:
        break;
    }
  }
  throw std::runtime_error("Tried to use the '<=' operator on a non-numeric JsonValue");
}

bool JsonValue::operator<=(const int integer) const {
  switch (type) {
    case JsonType::JINT:
      return value.intValue <= integer;
    case JsonType::JFLOAT:
      return value.floatValue <= static_cast<float>(integer);
    default:
      throw std::runtime_error("Tried to use the '<=' operator on a non-numeric JsonValue");
  }
}

bool JsonValue::operator<=(const float fp) const {
  switch (type) {
    case JsonType::JFLOAT:
      return value.floatValue <= fp;
    case JsonType::JINT:
      return static_cast<float>(value.intValue) <= fp;
    default:
      throw std::runtime_error("Tried to use the '<=' operator on a non-numeric JsonValue");
  }
}

bool operator<=(const int integer, const JsonValue& jVal) {
  return jVal >= integer;
}

bool operator<=(const float fp, const JsonValue& jVal) {
  return jVal >= fp;
}

bool JsonValue::operator>(const JsonValue& other) const {
  return !(*this <= other);
}

bool JsonValue::operator>(const int integer) const {
  return !(*this <= integer);
}

bool JsonValue::operator>(const float fp) const {
  return !(*this <= fp);
}

bool operator>(const int integer, const JsonValue& jVal) {
  return jVal < integer;
}

bool operator>(const float fp, const JsonValue& jVal) {
  return jVal < fp;
}

bool JsonValue::operator>=(const JsonValue& other) const {
  return !(*this < other);
}

bool JsonValue::operator>=(const int integer) const {
  return !(*this < integer);
}

bool JsonValue::operator>=(const float fp) const {
  return !(*this < fp);
}

bool operator>=(const int integer, const JsonValue& jVal) {
  return jVal <= integer;
}

bool operator>=(const float fp, const JsonValue& jVal) {
  return jVal <= fp;
}

JsonValue& JsonValue::operator++() {
  switch (type) {
    case JsonType::JINT:
      ++value.intValue;
      return *this;
    case JsonType::JFLOAT:
      ++value.floatValue;
      return *this;
    default:
      throw std::runtime_error("Attempted to increment a JsonValue of non-numeric type");
  }
}

bool JsonValue::operator!() {
  switch (type) {
    case JsonType::JBOOL:
      return !value.boolValue;
    case JsonType::JINT:
      return !value.intValue;
    case JsonType::JFLOAT:
      return !value.floatValue;
    case JsonType::JNULL:
      return true;
    default:
      throw std::runtime_error("Attempted to logical 'not' an invalid type");
  }
}

JsonValue JsonValue::operator++(int) {
  JsonValue before = *this;
  ++(*this);
  return before;
}

JsonValue& JsonValue::operator--() {
  switch (type) {
    case JsonType::JINT:
      --value.intValue;
      return *this;
    case JsonType::JFLOAT:
      --value.floatValue;
      return *this;
    default:
      throw std::runtime_error("Attempted to decrement a JsonValue of non-numeric type");
  }
}

JsonValue JsonValue::operator--(int) {
  JsonValue before = *this;
  --(*this);
  return before;
}

JsonValue JsonValue::operator+(const JsonValue& other) const {
  if (other.type == JsonType::JINT) {
    switch (type) {
      case JsonType::JINT:
        return value.intValue + other.value.intValue;
      case JsonType::JFLOAT:
        return value.floatValue + static_cast<float>(other.value.intValue);
      default:
        throw std::runtime_error("Attempted to add a valid JsonValue (JINT) to a non-numeric JsonValue");
        break;
    }
  }
  else if (other.type == JsonType::JFLOAT) {
    switch (type) {
      case JsonType::JINT:
        return static_cast<float>(value.intValue) + other.value.floatValue;
      case JsonType::JFLOAT:
        return value.floatValue + other.value.floatValue;
      default:
        throw std::runtime_error("Attempted to add a valid JsonValue (JFLOAT) to a non-numeric JsonValue");
        break;
    }
  }
  throw std::runtime_error("Attempted to add a non-numeric JsonValue to another JsonValue");
}

JsonValue JsonValue::operator+(const int integer) const {
  switch (type) {
    case JsonType::JINT:
      return value.intValue + integer;
    case JsonType::JFLOAT:
      return value.floatValue + static_cast<float>(integer); 
    default:
      throw std::runtime_error("Attempted to add a float to a non-numeric JsonValue");
  }
}

JsonValue JsonValue::operator+(const float fp) const {
  switch (type) {
    case JsonType::JINT:
      return static_cast<float>(value.intValue) + fp;
    case JsonType::JFLOAT:
      return value.floatValue + fp;
    default:
      throw std::runtime_error("Attempted to add a float to a non-numeric JsonValue");
  }
}

std::string JsonValue::operator+(const char* str) const {
  if (type == JsonType::JSTRING) {
    return *value.stringValue + str;
  }
  throw std::runtime_error("Attempted to concatenate std::string with non-string JsonValue");
}

std::string JsonValue::operator+(const std::string& str) const {
  if (type == JsonType::JSTRING) {
    return *value.stringValue + str;
  }
  throw std::runtime_error("Attempted to concatenate std::string with non-string JsonValue");
}

JsonValue& JsonValue::operator+=(const JsonValue& other) {
  switch (other.type) {
    case JsonType::JINT:
      return *this += other.value.intValue;
    case JsonType::JFLOAT:
      return *this += other.value.floatValue;
    case JsonType::JSTRING:
      return *this += *other.value.stringValue;
    default:
      throw std::runtime_error("Attempted to add and assign to incompatible JsonValue type"); 
  }
}

JsonValue& JsonValue::operator+=(const int integer) {
  switch (type) {
    case JsonType::JINT:
      value.intValue += integer;
      break;
    case JsonType::JFLOAT:
      value.floatValue += static_cast<float>(integer);
      break;
    default:
      throw std::runtime_error("Attempted to add an int to non-numeric JsonValue");
  }
  return *this;
}

JsonValue& JsonValue::operator+=(const float fp) {
  switch (type) {
    case JsonType::JFLOAT:
      value.floatValue += fp;
      break;
    case JsonType::JINT:
      setValue(static_cast<float>(value.intValue) + fp);
      break;
    default:
      throw std::runtime_error("Attempted to add a float to a non-numeric JsonValue");
  }
  return *this;
}

JsonValue& JsonValue::operator+=(const char* str) {
  if (type == JsonType::JSTRING) {
    *value.stringValue += str;
  }
  throw std::runtime_error("Attempted to add a const char* to a non-string JsonValue");
}

JsonValue& JsonValue::operator+=(const std::string& str) {
  if (type == JsonType::JSTRING) {
    *value.stringValue += str;
  }
  throw std::runtime_error("Attempted to add an std::string to a non-string JsonValue");
}

JsonValue JsonValue::operator-(const JsonValue& other) const {
  if (other.type == JsonType::JINT) {
    switch (type) {
      case JsonType::JINT:
        return value.intValue - other.value.intValue;
      case JsonType::JFLOAT:
        return value.floatValue - static_cast<float>(other.value.intValue);
      default:
        throw std::runtime_error("Attempted to subtract a JsonValue (JINT) from a non-numeric JsonValue");
    }
  }
  else if (other.type == JsonType::JFLOAT) {
    switch (type) {
      case JsonType::JFLOAT:
        return value.floatValue - other.value.floatValue;
      case JsonType::JINT:
        return static_cast<float>(value.intValue) - other.value.floatValue;
      default:
        throw std::runtime_error("Attempted to subtract a JsonValue (JFLOAT) from a non-numeric JsonValue");
    }
  }
  throw std::runtime_error("Attempted to subtract a non-numeric JsonValue from anothjer JsonValue");
}

JsonValue JsonValue::operator-(const int integer) const {
  switch (type) {
    case JsonType::JINT:
      return value.intValue - integer;
    case JsonType::JFLOAT:
      return value.floatValue - static_cast<float>(integer);
    default:
      throw std::runtime_error("Attempted to subtract a JsonValue (JINT) from a non-numeric JsonValue");
  }
}

JsonValue JsonValue::operator-(const float fp) const {
  switch (type) {
    case JsonType::JFLOAT:
      return value.floatValue - fp;
    case JsonType::JINT:
      return static_cast<float>(value.intValue) - fp;
    default:
      throw std::runtime_error("Attempted to subtract a JsonValue (JFLOAT) from a non-numeric JsonValue");
  }
}

JsonValue& JsonValue::operator-=(const JsonValue& other) {
  switch (other.type) {
    case JsonType::JINT:
      return *this -= other.value.intValue;
    case JsonType::JFLOAT:
      return *this -= other.value.floatValue;
    default:
      throw std::runtime_error("Attempted to subtract a non-numeric JsonValue from another JsonValue");
  }
}

JsonValue& JsonValue::operator-=(const int integer) {
  switch (type) {
    case JsonType::JINT:
      value.intValue -= integer;
      return *this;
    case JsonType::JFLOAT:
      value.floatValue -= static_cast<float>(integer);
      return *this;
    default:
      throw std::runtime_error("Attempted to subtract an int from a non-numeric JsonValue");
  }
}

JsonValue& JsonValue::operator-=(const float fp) {
  switch (type) {
    case JsonType::JFLOAT:
      value.floatValue -= fp;
      return *this;
    case JsonType::JINT:
      setValue(static_cast<float>(value.intValue) - fp);
      return *this;
    default:
      throw std::runtime_error("Attempted to subtract a float from a non-numeric JsonValue");
  }
}

JsonValue JsonValue::operator*(const JsonValue& other) const {
  if (other.type == JsonType::JINT) {
    switch (type) {
      case JsonType::JINT:
        return value.intValue * other.value.intValue;
      case JsonType::JFLOAT:
        return value.floatValue * static_cast<float>(other.value.intValue);
      default:
        throw std::runtime_error("Attempted to multiply an incompatible JsonValue by a JsonValue (JINT)");
    }
  }
  else if (other.type == JsonType::JFLOAT) {
    switch (type) {
      case JsonType::JFLOAT:
        return value.floatValue * other.value.floatValue;
      case JsonType::JINT:
        return static_cast<float>(value.intValue) * other.value.floatValue;
      default:
        throw std::runtime_error("Attempted to multiply an incompatible JsonValue by a JsonValue (JFLOAT)");
    }
  }
  throw std::runtime_error("Attempted to multiply a JsonValue by an incompatible type JsonValue");
}

JsonValue JsonValue::operator*(const int integer) const {
  switch (type) {
    case JsonType::JINT:
      return value.intValue * integer;
    case JsonType::JFLOAT:
      return value.floatValue * static_cast<float>(integer);
    default:
      throw std::runtime_error("Attempted to multiply an incompatible JsonValue by a JsonValue (JINT)");
  }
}

JsonValue JsonValue::operator*(const float fp) const {
  switch (type) {
    case JsonType::JFLOAT:
      return value.floatValue * fp;
    case JsonType::JINT:
      return static_cast<float>(value.intValue) * fp;
    default:
      throw std::runtime_error("Attempted to multiply an incompatible JsonValue by a JsonValue (JFLOAT)");
  }
}

JsonValue& JsonValue::operator*=(const JsonValue& other) {
  switch (other.type) {
    case JsonType::JINT:
      return *this *= other.value.intValue;
    case JsonType::JFLOAT:
      return *this *= other.value.floatValue;
    default:
      throw std::runtime_error("Attempted to multiply and assign a JsonValue using an incompatible JsonValue type");
  }
}

JsonValue& JsonValue::operator*=(const int integer) {
  switch (type) {
    case JsonType::JINT:
      value.intValue *= integer;
      break;
    case JsonType::JFLOAT:
      value.floatValue *= static_cast<float>(integer);
      break;
    default:
      throw std::runtime_error("Attempted to multiply and assign a JsonValue of incompatible type by an int");
  }
  return *this;
}

JsonValue& JsonValue::operator*=(const float fp) {
  switch (type) {
    case JsonType::JFLOAT:
      value.floatValue *= fp;
      break;
    case JsonType::JINT:
      setValue(static_cast<float>(value.intValue) * fp);
      break;
    default:
      throw std::runtime_error("Attempted to multiply and assign a JsonValue of incompatible type by a float");
  }
  return *this;
}

JsonValue JsonValue::operator/(const JsonValue& other) const {
  if (other.type == JsonType::JINT) {
    switch (type) {
      case JsonType::JINT:
        return value.intValue / other.value.intValue;
      case JsonType::JFLOAT:
        return value.floatValue / static_cast<float>(other.value.intValue);
      default:
        throw std::runtime_error("Attempted to divide and assign a JsonValue of incompatible type using a JsonValue (JINT)");
    }
  }
  else if (other.type == JsonType::JFLOAT) {
    switch (type) {
      case JsonType::JFLOAT:
        return value.floatValue / other.value.floatValue;
      case JsonType::JINT:
        return static_cast<float>(value.intValue) / other.value.floatValue;
      default:
        throw std::runtime_error("Attempted to divide and assign a JsonValue of incompatible type using a JsonValue (JFLOAT)");
    }
  }
  throw std::runtime_error("Attempted to divide a JsonValue by a non-numeric JsonValue");
}

JsonValue JsonValue::operator/(const int integer) const {
  switch (type) {
    case JsonType::JINT:
      return value.intValue / integer;
    case JsonType::JFLOAT:
      return value.floatValue / static_cast<float>(integer);
    default:
      throw std::runtime_error("Attempted to divide and assign a JsonValue of incompatible type by an int");
  }
}

JsonValue JsonValue::operator/(const float fp) const {
  switch (type) {
    case JsonType::JFLOAT:
      return value.floatValue / fp;
    case JsonType::JINT:
      return static_cast<float>(value.intValue) / fp;
    default:
      throw std::runtime_error("Attempted to divide and assign a JsonValue of incompatible type by a float");
  }
}

JsonValue& JsonValue::operator/=(const JsonValue& other) {
  switch (other.type) {
    case JsonType::JINT:
      return *this /= other.value.intValue;
    case JsonType::JFLOAT:
      return *this /= other.value.floatValue;
    default:
      throw std::runtime_error("Attempted to divide and assign a JsonValue by a JsonValue of incompatible type");
  }
}

JsonValue& JsonValue::operator/=(const int integer) {
  switch (type) {
    case JsonType::JINT:
      value.intValue /= integer;
      break;
    case JsonType::JFLOAT:
      value.floatValue /= static_cast<float>(integer);
      break;
    default:
      throw std::runtime_error("Attempted to divide and assign a JsonValue of incompatible type by an int");
  }
  return *this;
}

JsonValue& JsonValue::operator/=(const float fp) {
  switch (type) {
    case JsonType::JFLOAT:
      value.floatValue /= fp;
      break;
    case JsonType::JINT:
      setValue(static_cast<float>(value.intValue) / fp);
      break;
    default:
      throw std::runtime_error("Attempted to divide and assign a JsonValue of incompatible type by a float");
  }
  return *this;
}

// TODO: Implemend moduluses. apparently for floats c++ has an 'fmod' function. look into that.
JsonValue JsonValue::operator%(const JsonValue& other) const {
  if (other.type == JsonType::JINT) {
    switch (type) {
      case JsonType::JINT:
        return value.intValue % other.value.intValue;
      case JsonType::JFLOAT:
        return std::fmod(value.floatValue, static_cast<float>(other.value.intValue));
      default:
        throw std::runtime_error("Attempted to mod a JsonValue of non-numeric type by another JsonValue (JINT)");
    }
  }
  else if (other.type == JsonType::JFLOAT) {
    switch (type) {
      case JsonType::JFLOAT:
        return std::fmod(value.floatValue, other.value.floatValue);
      case JsonType::JINT:
        return std::fmod(static_cast<float>(value.intValue), other.value.floatValue);
      default:
        throw std::runtime_error("Attempted to mod a JsonValue of non-numeric type by another JsonValue (JFLOAT)");
    }
  }
  throw std::runtime_error("Attempted to mod a JsonValue by a JsonValue of non-numeric type");
}

JsonValue JsonValue::operator%(const int integer) const {
  switch (type) {
    case JsonType::JINT:
      return value.intValue % integer;
    case JsonType::JFLOAT:
      return std::fmod(value.floatValue, static_cast<float>(integer));
    default:
      throw std::runtime_error("Attempted to mod a JsonValue of non-numeric type by an int");
  }
}

JsonValue JsonValue::operator%(const float fp) const {
  switch (type) {
    case JsonType::JFLOAT:
      return std::fmod(value.floatValue, fp);
    case JsonType::JINT:
      return std::fmod(static_cast<float>(value.intValue), fp);
    default:
      throw std::runtime_error("Attempted to mod a JsonValue of non-numeric type by a float");
  }
}

JsonValue& JsonValue::operator%=(const JsonValue& other) {
  switch (other.type) {
    case JsonType::JINT:
      return *this %= other.value.intValue;
    case JsonType::JFLOAT:
      return *this %= other.value.floatValue;
    default:
      throw std::runtime_error("Attempted to mod a JsonValue by a non-numeric JsonValue");
  }
}

JsonValue& JsonValue::operator%=(const int integer) {
  switch (type) {
    case JsonType::JINT:
      value.intValue %= integer;
      break;
    case JsonType::JFLOAT:
      setValue(std::fmod(value.floatValue, static_cast<float>(integer)));
      break;
    default:
      throw std::runtime_error("Attempted to mod a non-numeric JsonValue by an int");
  }
  return *this;
}

JsonValue& JsonValue::operator%=(const float fp) {
  switch (type) {
    case JsonType::JFLOAT:
      setValue(std::fmod(value.floatValue, fp));
      break;
    case JsonType::JINT:
      setValue(std::fmod(static_cast<float>(value.intValue), fp));
      break;
    default:
      throw std::runtime_error("Attempted to mod a non-numeric JsonValue by a float");
  }
  return *this;
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

std::ostream& operator<<(std::ostream& out, JsonValue& jVal) {
  jVal.stringify(out);
  return out;
}

bool JsonValue::jfequal(const float f1, const float f2) {
  return std::abs(f1 - f2) <= JFLOAT_TOLERANCE;
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

void JsonValue::stringifyHelper(std::ostream& out, const unsigned short tabLevel, const bool isObjAttr) {
  if (!isObjAttr && tabLevel > 0) {
    out << std::endl;
    writeTabs(out, tabLevel);
  }

  if (type == JsonType::JOBJECT) {
    unsigned int mapSize = value.objectValue->size();

    out << '{';

    if (mapSize == 0) {
      out << ' ' << '}';
    }
    else {
      out << std::endl;
      for (auto& keyPair : *value.objectValue) {
        if (keyPair.second.getType() != JsonType::JINVALID) {
          writeTabs(out, tabLevel + 1);
          out << '"' << keyPair.first << '"' << ':' << ' ';
          keyPair.second.stringifyHelper(out, tabLevel + 1, true);

          if (--mapSize > 0) {
            out << ',';
          }
          out << std::endl;
        }
      }
      
      writeTabs(out, tabLevel);
      out << '}';
    }
  }
  else if (type == JsonType::JARRAY) {
    unsigned int arrSize = value.arrayValue->size();

    out << '[';

    if (arrSize == 0) {
      out << ' ' << ']';
    }
    else {
      for (JsonValue& item : *value.arrayValue) {
        item.stringifyHelper(out, tabLevel + 1);
        if (--arrSize > 0) {
          out << ',';
        }
      }
      out << std::endl;
      writeTabs(out, tabLevel);
      out << ']';
    }
  }
  else if (type == JsonType::JSTRING) {
    out << '"' << *value.stringValue << '"';
  }
  else if (type == JsonType::JINT) {
    out << value.intValue;
  }
  else if (type == JsonType::JFLOAT) {
    out << value.floatValue;
  }
  else if (type == JsonType::JBOOL) {
    out << (value.boolValue ? "true" : "false");
  }
  else if (type == JsonType::JNULL) {
    out << "null";
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

void JsonValue::writeTabs(std::ostream& out, unsigned short numTabs) {
  while (numTabs-- > 0) {
    out << '\t';
  }
}

bool operator==(const JsonArray& arr1, const JsonArray& arr2) {
  if (arr1.size() != arr2.size()) {
    return false;
  }
  
  for (unsigned int i = 0; i < arr1.size(); ++i) {
    if ( arr1[i] != arr2[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const JsonArray& arr1, const JsonArray& arr2) {
  return !(arr1 == arr2);
}

bool operator==(const JsonObject& obj1, const JsonObject& obj2) {
  if (obj1.size() != obj2.size()) {
    return false;
  }

  for (auto iter = obj1.begin(); iter != obj1.end(); ++iter) {
    const auto search = obj2.find(iter->first);
    if (search == obj2.end() || iter->second != search->second) {
      return false;
    }
  }
  return true;

}

bool operator!=(const JsonObject& obj1, const JsonObject& obj2) {
  return !(obj1 == obj2);
}
