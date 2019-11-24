#include "JsonParser.hpp"



JsonParser::JsonParser(const std::string& fileName)
{
  parseNewFile(fileName);
}

void JsonParser::parseNewFile(const std::string& fileName) {
  fin = std::ifstream(fileName);
  json = JsonValue();
  currentParseIndex = 0;

  while(currentPositionValid()) {
    const ParseType type = indicateNextType();
  }
}

bool JsonParser::currentPositionValid() {
  if (fin.bad()) return false;

  bool positionFine = currentParseIndex < line.length() - 1;
  if (positionFine) {
    return true;
  }
  else {
    currentParseIndex = 0;
    return !!getline(fin, line);
  }
}

ParseType JsonParser::indicateNextType(const char typeCloseChar) {
  while(currentPositionValid()) {
    const char currentChar = line[currentParseIndex++];

    // Skip whitespace before any operations
    if (currentChar == ' ') continue;

    switch (currentChar) {
      case '{': return ParseType::JOBJECT;
      case '"': return ParseType::JSTRING;
      case '[': return ParseType::JARRAY;
      case ',': return ParseType::JNEXTITEM;
      case 'n': return ParseType::JNULL;
      default: break;
    }

    if (isDigit(currentChar))
      return ParseType::JNUMBER;
    else if (currentChar == 't' || currentChar == 'f') 
      return ParseType::JBOOL;
    else if (currentChar == typeCloseChar)
      return ParseType::JENDITEM;
  }
}

void JsonParser::parseArray(JsonValue&) {

}
void parseBool(JsonValue&);
void parseFloat(JsonValue&);
void parseInt(JsonValue&);
void parseNull(JsonValue&);
void parseNumber(JsonValue&);
void parseObject(JsonValue&);
void parseString(JsonValue&);