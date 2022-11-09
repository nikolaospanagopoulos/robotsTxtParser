#include "UserAgent.hpp"
#include "Downloader.hpp"
#include <iostream>

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

bool UserAgent::canCrawlWebsite(const std::string websiteUrl) {

  if (!Downloader::validateUrl(websiteUrl) || websiteUrl.empty()) {
    std::cout << "url is not formated correctly" << std::endl;
    return false;
  }
  for (const auto &i : *websitesNotToParse) {
    size_t found = websiteUrl.find(i);
    if (found != std::string::npos) {
      return false;
    }
  }
  return true;
}
