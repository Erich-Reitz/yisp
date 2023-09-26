#include <array>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
#include <variant>

#include "../src/filereads.hpp"

#include "test_utils.hpp"
#include "minunit.hpp"

const char *runIntegrationTest(const std::string &testName, const char *failureMessage) {
  std::string pathToTestFromRootDir = "tests/tests/"  + testName + ".yisp";

  std::string pathToOutputFromRootDir = "tests/tests/"  + testName + "_output.txt";
  std::string expectedOutput = m_std::readFile(pathToOutputFromRootDir);
  std::string command = "./yisp " + pathToTestFromRootDir;
  std::string output = exec(command.c_str());
  mu_assert(failureMessage, expectedOutput == output);
  return 0;
}


// https://stackoverflow.com/a/52165057/15988683
std::string exec(const char *cmd) {
  std::array<char, 128> buffer;
  std::string result;

  auto pipe = popen(cmd, "r");

  if (!pipe) throw std::runtime_error("popen() failed!");

  while (!feof(pipe)) {
    if (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
      result += buffer.data();
  }

  auto rc = pclose(pipe);

  if (rc == EXIT_SUCCESS) { // == 0

  } else if (rc == EXIT_FAILURE) {

  }
  return result;
}