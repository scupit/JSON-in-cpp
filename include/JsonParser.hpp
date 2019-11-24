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
  JTRUE,
  JFALSE,
  JNULL,
  JNEXTITEM,
  JENDITEM,
  JENDFILE,
  JERROR
};

class JsonParser {
  private:
    std::ifstream fin;
    JsonValue json;
    std::string line;
    unsigned int currentParseIndex;

    inline bool isDigit(char c) { return c >= '0' && c <= '9'; }
    bool seqEqLineAtCurrentIndex(const std::string&);
  
  public:
    JsonParser(const std::string&);
    void parseNewFile(const std::string&);
    
  protected:
    bool currentPositionValid();
    ParseType indicateNextType(const char = '\\');
    void parseArray(JsonValue&);
    void parseTrue(JsonValue&);
    void parseFalse(JsonValue&);
    void parseNull(JsonValue&);
    void parseNumber(JsonValue&);
    void parseObject(JsonValue&);
    void parseString(JsonValue&);

    void setFloat(JsonValue&, const unsigned int, const unsigned int);
    void setInt(JsonValue&, const unsigned int, const unsigned int);
};

#endif