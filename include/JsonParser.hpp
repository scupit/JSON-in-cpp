#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <fstream>
#include <string>
#include "JsonValue.hpp"

enum class ParseType {
  JSTRING,
  JOBJECT,
  JARRAY,
  JNUMBER,
  JBOOL,
  JNULL,
  JNEXTITEM,
  JENDITEM
};

class JsonParser {
  private:
    std::ifstream fin;
    JsonValue json;
    std::string line;
    unsigned int currentParseIndex;

    inline bool isDigit(char c) { return c >= '0' && c <= '9'; }
  
  public:
    JsonParser(const std::string&);
    void parseNewFile(const std::string&);
    
  protected:
    bool currentPositionValid();
    ParseType indicateNextType(const char = '\\');
    void parseArray(JsonValue&);
    void parseBool(JsonValue&);
    void parseFloat(JsonValue&);
    void parseInt(JsonValue&);
    void parseNull(JsonValue&);
    void parseNumber(JsonValue&);
    void parseObject(JsonValue&);
    void parseString(JsonValue&);
};

#endif