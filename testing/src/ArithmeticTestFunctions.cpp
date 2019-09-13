#include "ArithmeticTestFunctions.hpp"
#include "TestPrinterFunctions.hpp"

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