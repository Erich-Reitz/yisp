#pragma once

#include <string>

namespace yisp {
int run(const std::string &contents);
[[nodiscard]] int runFile(const std::string &sourceFile);
}
