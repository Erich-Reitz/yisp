#pragma once

#include <string>
#include <vector>



std::string exec(const char *cmd);
const char *runIntegrationTest(const std::string &testName, const char *failureMessage);