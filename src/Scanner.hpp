#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Token.hpp"


namespace yisp::lexer {

struct Scanner {
  std::string source;
  size_t start = 0;
  size_t current = 0;
  size_t line = 1;
  std::vector<Token> tokens;
  explicit Scanner(std::string p_source) : source(std::move(p_source)) {}
};


[[nodiscard]] bool isAtEnd(const Scanner &scanner);
void scanToken(Scanner &scanner);
char advance(Scanner &scanner);
void addToken(Scanner &scanner, TokenType typ);
void addToken(Scanner &scanner, TokenType typ, std::optional<Atom> literal);
[[nodiscard]] char peek(const Scanner &scanner);
[[nodiscard]] char peekNext(const Scanner &scanner);

}

