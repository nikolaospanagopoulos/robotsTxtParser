#include "UserAgent.hpp"
#include "Downloader.hpp"
#include <boost/regex.hpp>
#include <boost/regex/v5/regex.hpp>
#include <iostream>
#include <regex>

UserAgent::UserAgent(std::string UserAgentName) : name{UserAgentName} {

  websitesNotToParse = new std::vector<std::string>{};
  websitesAllowed = new std::vector<std::string>{};
}
UserAgent::UserAgent(const UserAgent &source) : name{source.name} {
  websitesNotToParse = new std::vector<std::string>{};
  websitesAllowed = new std::vector<std::string>{};
  *websitesNotToParse = *source.websitesNotToParse;
  *websitesAllowed = *source.websitesAllowed;
}

UserAgent::UserAgent(UserAgent &&source)
    : name{source.name}, websitesNotToParse{source.websitesNotToParse},
      websitesAllowed{source.websitesAllowed} {
  source.websitesAllowed = nullptr;
  source.websitesNotToParse = nullptr;
}

UserAgent::~UserAgent() {
  delete websitesNotToParse;
  delete websitesAllowed;
}
/*
  boost::regex expression("/(.*)");
   if (foundAsterisk == robotsUrl.size() - 1) {
    std::string substringWithoutStar = robotsUrl.substr(0, foundAsterisk - 1);
    if (substringWithoutStar.back() == '/') {
      boost::cmatch what;
      if (boost::regex_match(websiteUrl.c_str(), what, expression)) {
        std::cout << "12345" << std::endl;
      }
    }
  }
*/
bool UserAgent::parseSymbols(const std::string &robotsUrl,
                             const std::string &websiteUrl) {

  std::regex specialChars{R"([-[\]{}()+?.,\^|#\s])"};

  std::regex wildCard{"\\*"};
  std::string sanitized = std::regex_replace(robotsUrl, specialChars, R"(\$&)");
  std::string moreS = std::regex_replace(sanitized, wildCard, R"(.*)");
  std::regex expression(moreS);
  std::smatch what;
  if (std::regex_search(websiteUrl, what, expression)) {
    return true;
  }
  return false;
}

bool UserAgent::canCrawlWebsite(const std::string websiteUrl) {

  if (!Downloader::validateUrl(websiteUrl) || websiteUrl.empty()) {
    std::cout << "url is not formated correctly" << std::endl;
    return false;
  }
  for (const auto &i : *websitesNotToParse) {
    size_t found = websiteUrl.find(i);
    if (parseSymbols(i, websiteUrl)) {
      return false;
    }
  }
  return true;
}
