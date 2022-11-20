#include "RobotsParser.hpp"
#include "iostream"
int main() {

  // parses robots.txt and gets all user agents
  std::vector<UserAgent> userAgents =
      RobotsParser::parseRobots("https://www.bbc.com/robots.txt");

  // prints all data
  // RobotsParser::printAllData(userAgents);

  // get specific user Agent
  UserAgent *ua = RobotsParser::getDataForUserAgent(userAgents, "*");

  for (auto i : *ua->websitesNotToParse) {
    std::cout << "disallowed: " << i << std::endl;
  }

  std::cout << "check if can be crawled" << std::endl;
  if (ua->canCrawlWebsite("https://www.bbc.com/food/recipes/shopping-list")) {
    std::cout << "can be crawled\n";
  } else {
    std::cout << "can not be crawled\n";
  }

  return 0;
}
