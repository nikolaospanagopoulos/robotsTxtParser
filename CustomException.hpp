#pragma once
#include <exception>
#include <iostream>

class CustomException : public std::exception {

private:
  char *message{};

public:
  CustomException(char *message) : message(message){};

  char *what() { return message; }
};
