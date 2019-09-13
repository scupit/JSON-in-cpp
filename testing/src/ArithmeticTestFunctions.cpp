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
    "Multiplying JINT by int literal",
    jVal * 10 == 120
  );

  printTestResultStatus(
    "Multiplying JINT by float literal",
    jVal * 10.5f == 126.0f
  );

  printTestResultStatus(
    "Multiplying JINT by JINT",
    jVal * JsonValue(10) == 120
  );

  printTestResultStatus(
    "Multiplying JINT by JFLOAT",
    jVal * JsonValue(10.5f) == 126.0f
  );

  jVal *= 10;

  printTestResultStatus(
    "Multiplying and assigning int literal to JINT (type)",
    jVal.getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Multiplying and assigning int literal to JINT (value)",
    jVal == 120
  );

  jVal *= 10.5f;

  printTestResultStatus(
    "Multiplying and assigning float literal to JINT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Multiplying and assigning float literal to JINT (value)",
    jVal == 1260
  );

  jVal *= 10.5f;

  printTestResultStatus(
    "Multiplying and assigning float literal to JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Multiplying and assigning float literal to JFLOAT (value)",
    jVal == 13230.0f
  );

  jVal *= 10;

  printTestResultStatus(
    "Multiplying and assigning int literal to JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Multiplying and assigning int literal to JFLOAT (value)",
    jVal == 132300.0f
  );

  jVal *= JsonValue(10.5f);

  printTestResultStatus(
    "Multiplying and assigning JFLOAT to JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Multiplying and assigning JFLOAT to JFLOAT (value)",
    jVal == 1389150.0f
  );

  jVal *= JsonValue(10);

  printTestResultStatus(
    "Multiplying and assigning JINT to JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Multiplying and assigning JINT to JFLOAT (value)",
    jVal == 13891500.0f
  );
}

void testDivisionOperators(JsonValue& jVal) {
  jVal = 480;

  printTestResultStatus(
    "Dividing JINT by int literal",
    jVal / 2 == 240
  );

  printTestResultStatus(
    "Dividing JINT by float literal",
    jVal / 2.5f == 192.0f
  );

  printTestResultStatus(
    "Dividing JINT by JINT",
    jVal / JsonValue(2) == 240.0f
  );

  printTestResultStatus(
    "Dividing JINT by JFLOAT",
    jVal / JsonValue(2.5f) == 192.0f
  );

  jVal /= 4;

  printTestResultStatus(
    "Dividing and assigning int literal from JINT (type)",
    jVal.getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Dividing and assigning int literal from JINT (value)",
    jVal == 120
  );

  jVal /= 2.5f;

  printTestResultStatus(
    "Dividing and assigning float literal from JINT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Dividing and assigning float literal from JINT (value)",
    jVal == 48.0f
  );

  jVal /= 2.5f;

  printTestResultStatus(
    "Dividing and assigning float literal from JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Dividing and assigning float literal from JFLOAT (value)",
    jVal == 19.2f
  );

  jVal /= 2;

  printTestResultStatus(
    "Dividing and assigning int literal from JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Dividing and assigning int literal from JFLOAT (value)",
    jVal == 9.6f
  );

  jVal /= JsonValue(2.5f);

  printTestResultStatus(
    "Dividing and assigning JFLOAT from JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Dividing and assigning JFLOAT from JFLOAT (value)",
    jVal == 3.84f
  );

  jVal /= JsonValue(2);

  printTestResultStatus(
    "Dividing and assigning JINT from JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Dividing and assigning JINT from JFLOAT (value)",
    jVal == 1.92f
  );
}

void testModulusOperators(JsonValue& jVal) {
  jVal = 123;

  printTestResultStatus(
    "Modding JINT by int literal",
    jVal % 4 == 3
  );

  printTestResultStatus(
    "Modding JINT by float literal",
    jVal % 2.5f == 0.5000f
  );

  printTestResultStatus(
    "Modding JINT by JINT",
    jVal % JsonValue(4) == 3
  );

  printTestResultStatus(
    "Modding JINT by JFLOAT",
    jVal % JsonValue(2.5f) == 0.5000f
  );

  jVal %= 4;

  printTestResultStatus(
    "Modding and assigning int literal from JINT (type)",
    jVal.getType() == JsonType::JINT
  );

  printTestResultStatus(
    "Modding and assigning int literal from JINT (value)",
    jVal == 3
  );

  jVal = 123;
  jVal %= 2.5f;

  printTestResultStatus(
    "Modding and assigning float literal from JINT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Modding and assigning float literal from JINT (value)",
    jVal == 0.5000f
  );


  jVal = 123.0f;
  jVal %= 2.5f;

  printTestResultStatus(
    "Modding and assigning float literal from JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Modding and assigning float literal from JFLOAT (value)",
    jVal == 0.5000f
  );

  jVal = 123.0f;
  jVal %= 4;

  printTestResultStatus(
    "Modding and assigning int literal from JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Modding and assigning int literal from JFLOAT (value)",
    jVal == 3.0f
  );

  jVal = 123.0f;
  jVal %= JsonValue(2.5f);

  printTestResultStatus(
    "Modding and assigning JFLOAT from JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Modding and assigning JFLOAT from JFLOAT (value)",
    jVal == 0.5000f
  );

  jVal = 123.0f;
  jVal %= JsonValue(4);

  printTestResultStatus(
    "Modding and assigning JINT from JFLOAT (type)",
    jVal.getType() == JsonType::JFLOAT
  );

  printTestResultStatus(
    "Modding and assigning JINT from JFLOAT (value)",
    jVal == 3.0f
  );
}

void testIncrementOperators(JsonValue& jVal) {
  jVal = 0;

  printTestResultStatus(
    "Postfix incrementation with JINT",
    jVal++ == 0
  );

  printTestResultStatus(
    "Prefix incrementation with JINT",
    ++jVal == 2
  );

  printTestResultStatus(
    "Postfix decrementation with JINT",
    jVal-- == 2
  );
  
  printTestResultStatus(
    "Prefix incrementation with JINT",
    --jVal == 0
  );

  jVal = 0.0f;

  printTestResultStatus(
    "Postfix decrementation  with JFLOAT",
    jVal++ == 0.0f
  );

  printTestResultStatus(
    "Prefix incrementation with JFLOAT",
    ++jVal == 2.0f
  );

  printTestResultStatus(
    "Postfix decrementation with JFLOAT",
    jVal-- == 2.0f
  );
  
  printTestResultStatus(
    "Prefix decrementation with JFLOAT",
    --jVal == 0.0f
  );
}