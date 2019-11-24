#include "JsonParser.hpp"
#include <stdexcept>

JsonParser::JsonParser(const std::string& fileName) {
  parseNewFile(fileName);
}

JsonParser::JsonParser(const std::string& fileName, JsonValue& jsonIn, const bool shouldCopyIntoLocalJson) {
  parseNewFile(fileName, jsonIn, shouldCopyIntoLocalJson);
}

void JsonParser::parseNewFile(const std::string& fileName) {
  parseNewFile(fileName, json = JsonValue());
}

void JsonParser::parseNewFile(const std::string& fileName, JsonValue& jsonIn, const bool shouldCopyIntoLocalJson) {
  fin = std::ifstream(fileName);
  currentParseIndex = 0;

  parseInto(jsonIn, determineNextType());
  fin.close();

  if (shouldCopyIntoLocalJson) {
    json = jsonIn;
  }
}

// Middle function between parsing, determines which function to call based on the parse type
void JsonParser::parseInto(JsonValue& jsonIn, const ParseType typeToParse) {
  switch (typeToParse) {
    case ParseType::JSTRING:
      parseString(jsonIn);
      break;
    case ParseType::JARRAY:
      parseArray(jsonIn);
      break;
    case ParseType::JOBJECT:
      parseObject(jsonIn);
      break;
    case ParseType::JNUMBER:
      parseNumber(jsonIn);
      break;
    case ParseType::JNULL:
      parseNull(jsonIn);
      break;
    case ParseType::JTRUE:
      parseTrue(jsonIn);
      break;
    case ParseType::JFALSE:
      parseFalse(jsonIn);
      break;
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

ParseType JsonParser::determineNextType(const char typeCloseChar) {
  while(currentPositionValid()) {
    const char currentChar = line[currentParseIndex++];

    // Skip whitespace before any operations
    if (currentChar == ' ') continue;

    switch (currentChar) {
      case '{': return ParseType::JOBJECT;
      case '"': return ParseType::JSTRING;
      case '[': return ParseType::JARRAY;
      case ',': return ParseType::JNEXTITEM;
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

void JsonParser::parseArray(JsonValue& jsonIn) {
  ParseType nextType;
  jsonIn.changeType(JsonType::JARRAY);

  while ((nextType = determineNextType(']')) != ParseType::JENDITEM && nextType != ParseType::JENDFILE) {
    if (nextType != ParseType::JNEXTITEM) {
      jsonIn.getAsVector().push_back(JsonValue());
      parseInto(jsonIn.getAsVector().back(), nextType);
    }
  }
}

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
  unsigned int initialCharIndex = currentParseIndex - 1;

  // Detect negatives
  if (initialCharIndex >= 1 && line[initialCharIndex - 1] == '-') {
    --initialCharIndex;
  }

  // Traverse to next character which is not a digit
  while(isDigit(line[currentParseIndex++]));

  if (line[currentParseIndex - 1] == '.') {
    while(isDigit(line[currentParseIndex++]));
    setFloat(jsonIn, initialCharIndex, currentParseIndex - 1);
  }
  else {
    setInt(jsonIn, initialCharIndex, currentParseIndex - 1);
  }
}

// ParseType 'next item' is currently not used
void JsonParser::parseObject(JsonValue& jsonIn) {
  ParseType nextType;
  jsonIn.changeType(JsonType::JOBJECT);

  // While the next type is not the end of the object
  while((nextType = determineNextType('}')) != ParseType::JENDITEM && nextType != ParseType::JENDFILE) {
    if (nextType == ParseType::JSTRING) {
      // Parses the next item into the JsonObject added to jsonIn.
      const std::string key = parseKey();
      parseInto(jsonIn[key], determineNextType());
    }
  }
}

void JsonParser::parseString(JsonValue& jsonIn) {
  const unsigned int initialStringIndex = currentParseIndex;
  traverseParseIndexToEndingQuote();

  // currentParseIndex is the index of the string's ending quote.
  // If the index is unchanged, assumed to be an empty string.
  jsonIn = initialStringIndex == currentParseIndex
    ? ""
    : line.substr(initialStringIndex, currentParseIndex - initialStringIndex);

  // Set parse index to the next character, so that the next type to parse can be
  // correctly determined
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

// Should only be called when parsing an object key.
// NOTE: The very next 'determineNextType()' after this function will return the object value 
// type to be parsed. 
const std::string JsonParser::parseKey() {
  const unsigned int initialIndex = currentParseIndex;
  traverseParseIndexToEndingQuote();
  const unsigned int endingQuoteIndex = currentParseIndex;

  // Sets the current parsing character to the one after the colon, so that the next
  // type to be parsed can be correctly determined.
  while (line[currentParseIndex++] != ':');
  return line.substr(initialIndex, endingQuoteIndex - initialIndex);
}

// Sequential string equality, which also increments the currentParseIndex
bool JsonParser::seqEqLineAtCurrentIndex(const std::string& strToMatch) {
  for (int i = 0; i < strToMatch.length(); ++i) {
    if (line[currentParseIndex++] != strToMatch[i])
      return false;
  }
  return true;
}

// currentParseIndex will be on the string's ending quote.
// ONLY USED WHEN PARSING A STRING
void JsonParser::traverseParseIndexToEndingQuote() {
  while (line[currentParseIndex] != '"') {
    if (line[currentParseIndex] == '\\') {
      ++currentParseIndex;
    }
    ++currentParseIndex;
  }
}