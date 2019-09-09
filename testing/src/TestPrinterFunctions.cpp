#include "TestPrinterFunctions.hpp"

#include <iostream>

void printBasicMessage(const std::string& message, const std::string& color) {
  if (color == TEXT_RESET) {
    std::cout << message;
  }
  else {
    system(("echo " + color + message + TEXT_RESET).c_str());
  }
}

void printFail(const std::string& whatTest) {
  system(("echo " TEXT_RED + whatTest + " - FAILED" TEXT_RESET "\n").c_str());
}

void printNewline(unsigned int numNewlines) {
  while (numNewlines > 0) {
    std::cout << std::endl;
  }
}

void printSuccess(const std::string& whatTest) {
  system(("echo " TEXT_GREEN + whatTest + TEXT_RESET " - PASSED" "\n").c_str());
}

void printTestGroup(const std::string& groupName, void (*testFunction)(JsonValue&)) {
  JsonValue jVal;
  printBasicMessage("\n" HEADING_SEPARATOR "\n");
  printBasicMessage("Now testing " + groupName, TEXT_YELLOW);
  printBasicMessage(HEADING_SEPARATOR "\n");
  testFunction(jVal);
  printBasicMessage(HEADING_SEPARATOR "\n");
}

void printTestResultStatus(const std::string& whatTest, const bool status) {
  if (status) {
    printSuccess(whatTest);
  }
  else {
    printFail(whatTest);
  }
}

