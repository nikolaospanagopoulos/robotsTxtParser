#pragma once
#include <string>
#include <vector>

class UserAgent {

private:
public:
  bool canCrawlWebsite(const std::string websiteUrl);
  std::string name;
  UserAgent(std::string UserAgentName);
  UserAgent(const UserAgent &source);
  UserAgent(UserAgent &&source);
  std::vector<std::string> *websitesNotToParse{};
  std::vector<std::string> *websitesAllowed{};
  ~UserAgent();
};
