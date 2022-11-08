#include "RobotsParser.hpp"
#include "Downloader.hpp"
#include "Tokenizer.hpp"
#include <cctype>
#include <sstream>

std::vector<UserAgent> RobotsParser::parseRobots(const std::string url) {

  std::string *response = Downloader::requestData(url);

  std::stringstream allWords{*response};

  if (response) {
    delete response;
  }
  return Tokenizer::parse(allWords);
}

void RobotsParser::printAllData(const std::vector<UserAgent> &allUserAgents) {
  Tokenizer::printAllData(allUserAgents);
}

UserAgent *RobotsParser::getDataForUserAgent(std::vector<UserAgent> &allAgents,
                                             const std::string UserAgentName) {

  if (allAgents.empty()) {
    std::cout << "not available user agents" << std::endl;
    return nullptr;
  }
  for (auto &i : allAgents) {
    std::cout << i.name << ":" << UserAgentName << std::endl;
    if (i.name == UserAgentName) {
      return &i;
    }
  }
  std::cout << "couldnt find user agent" << std::endl;
  return nullptr;
}
