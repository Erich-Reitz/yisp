#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "filereads.hpp"

namespace m_std {

void openFile(std::ifstream &input, const std::string &filename) ;
std::string readFile(std::ifstream &input);

static std::string ERROR = "ERROR::";

void openFile(std::ifstream &input, const std::string &filename) {
  input.open(filename);
  if (!input.is_open()) {
    throw std::runtime_error(ERROR + "Could not open " + filename);
  }
}

std::string readFile(std::ifstream &input) {
  std::stringstream ss;
  std::string line;
  while (std::getline(input, line)) {
    ss << line << '\n';
  }
  return ss.str();
}

std::string readFile(const std::string &filename) {
  std::ifstream input;
  openFile(input, filename);
  return readFile(input);
}

}