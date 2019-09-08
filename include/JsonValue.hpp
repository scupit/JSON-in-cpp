#ifndef JSONVALUE_HPP
#define JSONVALUE_HPP

#include <unordered_map>
#include <vector>

// Define possible json types
enum class JsonType {
  JARRAY,
  JOBJECT,
  JSTRING,
  JINT,
  JFLOAT,
  JBOOL,
  JNULL,
  JINVALID
};

// Forward declare JsonValue so the typedefs do not break.
class JsonValue;

typedef std::vector<JsonValue> JsonArray;
typedef std::unordered_map<std::string, JsonValue> JsonObject;

// Union containing possible data for each type other than JNULL.
// No need to include null item since it can be inferred from the type anyways.
union Value {
  int intValue;
  float floatValue;
  bool boolValue;
  std::string* stringValue;
  JsonArray* arrayValue;
  JsonObject* objectValue;
};

// Class for managing types and value
class JsonValue {
  private:
    JsonType type;
    Value value;

  public:
    JsonValue();
    JsonValue(const JsonType);
    JsonValue(const int);
    JsonValue(const float);
    JsonValue(const bool);
    JsonValue(const std::string&);
    JsonValue(const JsonArray&);
    JsonValue(const JsonObject&);
    JsonValue(const JsonValue&);
    ~JsonValue();

    inline JsonType getType() { return type; }

    void changeType(const JsonType);
    void resetValue();
    void setValue(const int);
    void setValue(const float);
    void setValue(const bool);
    void setValue(const std::string&);
    void setValue(const JsonArray&);
    void setValue(const JsonObject&);

    int getAsInt();
    float getAsFloat();
    bool getAsBool();
    std::string& getAsString();
    JsonArray& getAsVector();
    JsonObject& getAsMap();

  private:
    void destroyCurrentValue();
    void typeChangeHelper(const JsonType);
};

#endif