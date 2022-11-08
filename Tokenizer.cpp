#include "Tokenizer.hpp"
#include "UserAgent.hpp"
#include <algorithm>
#include <cctype>
#include <vector>

std::string removeSpace(std::string UserAgentName) {

  UserAgentName.erase(
      std::remove_if(UserAgentName.begin(), UserAgentName.end(), ::isspace),
      UserAgentName.end());

  return UserAgentName;
}

std::vector<UserAgent> Tokenizer::parse(std::stringstream &allWords) {

  std::string word;
  std::vector<std::string> allTokens{};
  while (std::getline(allWords, word)) {

    size_t position{};
    std::string token;

    std::string delimeter{":"};
    while ((position = word.find(delimeter)) != std::string::npos) {
      token = word.substr(0, position);
      allTokens.push_back(token);
      token = word.substr(position + 1);
      allTokens.push_back(token);
      word.erase();
    }
  }

  std::vector<UserAgent> userAgents;
  int userAgentIndex = 0;

  for (size_t i{}; i < allTokens.size(); i++) {
    if (allTokens[i] == "User-agent" || allTokens[i] == "User-Agent") {
      std::string userAgentName = removeSpace(allTokens[i + 1]);
      UserAgent us{userAgentName};
      userAgents.push_back(std::move(us));
      userAgentIndex = 0 ? 0 : userAgentIndex + 1;
    }
    if (allTokens[i] == "Disallow") {
      std::string websiteNotToAllow = removeSpace(allTokens[i + 1]);
      userAgents[userAgents.size() - 1].websitesNotToParse->push_back(
          websiteNotToAllow);
    }
    if (allTokens[i] == "Allow") {
      std::string websiteToAllow = removeSpace(allTokens[i + 1]);
      userAgents[userAgents.size() - 1].websitesAllowed->push_back(
          websiteToAllow);
    }
  }

  return userAgents;
}

void Tokenizer::printAllData(const std::vector<UserAgent> &userAgents) {
  for (auto &i : userAgents) {
    std::cout << "name: " << i.name << std::endl;
    for (auto &f : *i.websitesNotToParse) {
      std::cout << "disallowed: " << f << std::endl;
    }
    for (auto &u : *i.websitesAllowed) {
      std::cout << "allowed: " << u << std::endl;
    }
  }
}
