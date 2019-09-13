#include "ArithmeticTestFunctions.hpp"
#include "TestPrinterFunctions.hpp"

#include <cstdio>

void testAdditionOperators(JsonValue& jVal) {
  jVal = 12;

  printTestResultStatus(
    "Adding int literal to JINT",
    jVal + 10 == 22
  );

  printTestResultStatus(
    "Adding float literal to JINT",
    jVal + 10.2f == 22.2f
  );

  printTestResultStatus(
    "Adding JINT to JINT",
    jVal + JsonValue(10) == 22
  );

  printTestResultStatus(
    "Adding JFLOAT to JINT",
    jVal + JsonValue(10.2f) == 22.2f
  );

  jVal += 10;

  printTestResultStatus(
    "Adding and assigning int literal to JINT (type)",
    jVal.getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Adding and assigning int literal to JINT (value)",
    jVal == 22
  );

  jVal += 10.2f;

  printTestResultStatus(
    "Adding and assigning float literal to JINT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding and assigning float literal to JINT (value)",
    jVal == 32.2f
  );

  jVal += 10.2f;

  printTestResultStatus(
    "Adding and assigning float literal to JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding and assigning float literal to JFLOAT (value)",
    jVal == 42.4f
  );

  jVal += 10;

  printTestResultStatus(
    "Adding and assigning int literal to JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding and assigning int literal to JFLOAT (value)",
    jVal == 52.4f
  );

  jVal += JsonValue(10.2f);

  printTestResultStatus(
    "Adding and assigning JFLOAT to JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding and assigning JFLOAT to JFLOAT (value)",
    jVal == 62.6f
  );

  jVal += JsonValue(10);

  printTestResultStatus(
    "Adding and assigning JINT to JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding and assigning JINT to JFLOAT (value)",
    jVal == 72.6f
  );
}

void testSubtractionOperators(JsonValue& jVal) {
  jVal = 90;

  printTestResultStatus(
    "Subtracting int literal from JINT",
    jVal - 10 == 80
  );

  printTestResultStatus(
    "Subtracting float literal from JINT",
    jVal - 10.2f == 79.8f
  );

  printTestResultStatus(
    "Subtracting JINT from JINT",
    jVal - JsonValue(10) == 80
  );

  printTestResultStatus(
    "Subtracting JFLOAT from JINT",
    jVal - JsonValue(10.2f) == 79.8f
  );

  jVal -= 10;

  printTestResultStatus(
    "Subtracting and assigning int literal from JINT (type)",
    jVal.getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Subtracting and assigning int literal from JINT (value)",
    jVal == 80
  );

  jVal -= 10.2f;

  printTestResultStatus(
    "Subtracting and assigning float literal from JINT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Subtracting and assigning float literal from JINT (value)",
    jVal == 69.8f
  );

  jVal -= 10.2f;

  printTestResultStatus(
    "Subtracting and assigning float literal from JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Subtracting and assigning float literal from JFLOAT (value)",
    jVal == 59.6f
  );

  jVal -= 10;

  printTestResultStatus(
    "Subtracting and assigning int literal from JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Subtracting and assigning int literal from JFLOAT (value)",
    jVal == 49.6f
  );

  jVal -= JsonValue(10.2f);

  printTestResultStatus(
    "Subtracting and assigning JFLOAT from JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Subtracting and assigning JFLOAT from JFLOAT (value)",
    jVal == 39.4f
  );

  jVal -= JsonValue(10);

  printTestResultStatus(
    "Subtracting and assigning JINT from JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Subtracting and assigning JINT from JFLOAT (value)",
    jVal == 29.4f
  );
}

void testMultiplicationOperators(JsonValue& jVal) {
  jVal = 12;

  printTestResultStatus(
    "Adding int literal to JINT",
    jVal * 10 == 120
  );

  printTestResultStatus(
    "Adding float literal to JINT",
    jVal * 10.5f == 126.0f
  );

  printTestResultStatus(
    "Adding JINT to JINT",
    jVal * JsonValue(10) == 120
  );

  printTestResultStatus(
    "Adding JFLOAT to JINT",
    jVal * JsonValue(10.5f) == 126.0f
  );

  jVal *= 10;

  printTestResultStatus(
    "Adding and assigning int literal to JINT (type)",
    jVal.getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Adding and assigning int literal to JINT (value)",
    jVal == 120
  );

  jVal *= 10.5f;

  printTestResultStatus(
    "Adding and assigning float literal to JINT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding and assigning float literal to JINT (value)",
    jVal == 1260
  );

  jVal *= 10.5f;

  printTestResultStatus(
    "Adding and assigning float literal to JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding and assigning float literal to JFLOAT (value)",
    jVal == 13230.0f
  );

  jVal *= 10;

  printTestResultStatus(
    "Adding and assigning int literal to JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding and assigning int literal to JFLOAT (value)",
    jVal == 132300.0f
  );

  jVal *= JsonValue(10.5f);

  printTestResultStatus(
    "Adding and assigning JFLOAT to JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding and assigning JFLOAT to JFLOAT (value)",
    jVal == 1389150.0f
  );

  jVal *= JsonValue(10);

  printTestResultStatus(
    "Adding and assigning JINT to JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Adding and assigning JINT to JFLOAT (value)",
    jVal == 13891500.0f
  );
}

