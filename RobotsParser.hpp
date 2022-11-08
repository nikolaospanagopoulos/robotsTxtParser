#pragma once
#include <vector>

#include "UserAgent.hpp"
class RobotsParser {

public:
  static std::vector<UserAgent> parseRobots(const std::string url);
  static void printAllData(const std::vector<UserAgent> &allUserAgents);
  static UserAgent *getDataForUserAgent(std::vector<UserAgent> &allAgents,
                                        const std::string UserAgentName = "*");
};
