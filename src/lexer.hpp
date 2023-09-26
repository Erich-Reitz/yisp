#pragma once

#include <string>
#include <vector>


#include "Token.hpp"


namespace yisp::lexer {
[[nodiscard]] std::vector<Token> lex(const std::string &text);
}
