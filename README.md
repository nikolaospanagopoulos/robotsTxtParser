# A C++ robots.txt parser

### just close the repo and include the RobotsParser file

### important! you need to have libcurl installed

### The static methods

##### RobotsParser::parseRobots("website you want to parse")

###### returns a vector of UserAgent Objects

&nbsp;

##### RobotsParser::getDataForUserAgent(userAgents, "the name of user agent you want(default \*)");

###### returns the a pointer to the UserAgent object

&nbsp;

##### RobotsParser::printAllData(userAgents);

###### takes as argument the userAgent vector that the previous function returns, and prints all data

&nbsp;

### The UserAgent object methods

##### canCrawlWebsite("example website url")

###### returns a bool value (can be crawled or not)

&nbsp;

### For more details follow the example in example.cpp file
