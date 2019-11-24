#include "JsonParser.hpp"
#include <stdexcept>

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

  bool positionFine = currentParseIndex < line.length();
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
      default: break;
    }

    if (isDigit(currentChar))
      return ParseType::JNUMBER;
    else if (currentChar == 't')
      return ParseType::JTRUE;
    else if (currentChar == 'f')
      return ParseType::JFALSE;
    else if (currentChar == typeCloseChar)
      return ParseType::JENDITEM;
    else if (currentChar == 'n')
      return ParseType::JNULL;
  }
  return ParseType::JENDFILE;
}

void parseArray(JsonValue&);
void JsonParser::parseTrue(JsonValue& jsonIn) {
  if (seqEqLineAtCurrentIndex("rue")) {
    jsonIn = true;
  }
  else {
    throw std::runtime_error("Invalid json when parsing for true");
  }
};

void JsonParser::parseFalse(JsonValue& jsonIn) {
  if (seqEqLineAtCurrentIndex("alse")) {
    jsonIn = false;
  }
  else {
    throw std::runtime_error("Invalid json when parsing for false");
  }
}

void JsonParser::parseNull(JsonValue& jsonIn) {
  if (seqEqLineAtCurrentIndex("ull")) {
    jsonIn = JsonValue(nullptr);
  }
  else {
    throw std::runtime_error("Invalid Json when parsing for null value");
  }
}

void JsonParser::parseNumber(JsonValue& jsonIn) {
  const unsigned int initialCharIndex = currentParseIndex;

  // Traverse to next character which is not a digit
  while(isDigit(line[currentParseIndex++]));

  if (line[currentParseIndex] == '.') {
    while(!isDigit(line[currentParseIndex++]));
    setFloat(jsonIn, initialCharIndex, currentParseIndex - 1);
  }
  else {
    setInt(jsonIn, initialCharIndex, currentParseIndex - 1);
  }
}

void parseObject(JsonValue&);
void JsonParser::parseString(JsonValue& jsonIn) {
  const unsigned int initialStringIndex = currentParseIndex;

  while (line[currentParseIndex] != '"') {
    if (line[currentParseIndex] == '\\') {
      ++currentParseIndex;
    }
    ++currentParseIndex;
  }

  // currentParseIndex is the index of the string's ending quote.
  // If the index is unchanged, assumed to be an empty string.
  jsonIn = initialStringIndex == currentParseIndex
    ? ""
    : line.substr(initialStringIndex, currentParseIndex - initialStringIndex);
  ++currentParseIndex;
}

void JsonParser::setFloat(JsonValue& jsonIn, const unsigned int startIndex, const unsigned int endIndex) {
  jsonIn = std::stof(line.substr(startIndex, endIndex - startIndex));
}

void JsonParser::setInt(JsonValue& jsonIn, const unsigned int startIndex, const unsigned int endIndex) {
  jsonIn = std::stoi(line.substr(startIndex, endIndex - startIndex));
}

// ################################################################################ 
// PRIVATE
// ################################################################################ 

bool JsonParser::seqEqLineAtCurrentIndex(const std::string& strToMatch) {
  for (int i = 0; i < strToMatch.length(); ++i) {
    if (line[currentParseIndex++] != strToMatch[i])
      return false;
  }
  return true;
}