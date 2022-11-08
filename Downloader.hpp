#pragma once
#include <curl/curl.h>
#include <string>

class Downloader {

private:
public:
  static bool validateUrl(const std::string &url);
  static std::string *requestData(const std::string url);
};
