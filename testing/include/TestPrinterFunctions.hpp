#ifndef TESTPRINTERFUNCTIONS_HPP
#define TESTPRINTERFUNCTIONS_HPP

#define CONSOLE_PRINTS_IN_COLOR 0

#define TEXT_RESET "\x1b[0m"
#define TEXT_RED "\x1b[0;31m"
#define TEXT_GREEN "\x1b[0;32m"
#define TEXT_YELLOW "\x1b[0;33m"

#define HEADING_SEPARATOR "-----------------------------------------------------------------------"

#include "JsonValue.hpp"
#include <string>

void printBasicMessage(const std::string&, const std::string& color = TEXT_RESET);
void printFail(const std::string&);
void printNewline(unsigned int = 1);
void printSuccess(const std::string&);
void printTestGroup(const std::string&, void (*)(JsonValue&));
void printTestResultStatus(const std::string&, const bool);

#endif