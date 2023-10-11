#pragma once

#include <vector>

#include "ConsCell.hpp"
#include "Expression.hpp"
#include "Token.hpp"


namespace yisp::parser {


class Parser {
 public:
  explicit Parser(const std::vector<Token> &tokens);

  std::vector<Token> tokens;
  size_t current;

};

std::vector<std::shared_ptr<SExpression>> parse(const std::vector<Token> &tokens);
}

