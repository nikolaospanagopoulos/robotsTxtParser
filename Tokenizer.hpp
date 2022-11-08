#pragma once
#include "UserAgent.hpp"
#include <iostream>
#include <sstream>
#include <string>

class Tokenizer {
public:
  static std::vector<UserAgent> parse(std::stringstream &inProgram);
  static void printAllData(const std::vector<UserAgent> &userAgents);
};
