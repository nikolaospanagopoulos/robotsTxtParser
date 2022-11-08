#include "Downloader.hpp"
#include "CustomException.hpp"
#include <curl/curl.h>
#include <regex>

bool Downloader::validateUrl(const std::string &url) {

  std::regex urlRegex{
      "((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//"
      "=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)"};

  if (std::regex_match(url.c_str(), urlRegex)) {
    return true;
  }
  return false;
}

size_t writeResponseToString(char *contents, size_t size, size_t nmemb,
                             void *userData) {
  size_t newLength = size * nmemb;
  try {
    ((std::string *)userData)->append((char *)contents, newLength);
  } catch (std::bad_alloc &e) {
    std::cerr << e.what() << std::endl;
  }
  return newLength;
}

size_t (*callbackToWrite)(char *, size_t, size_t,
                          void *) = writeResponseToString;

std::string *Downloader::requestData(const std::string url) {
  if (!validateUrl(url)) {
    return nullptr;
  }

  CURL *curl{};
  CURLcode res{};
  std::string *response = new std::string{};

  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackToWrite);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      delete response;
      return nullptr;
    }
  }

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return response;
}
