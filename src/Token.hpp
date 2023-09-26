#pragma once

#include <string>
#include <optional>

#include "Atom.hpp"

namespace yisp {
enum class TokenType {
  LEFT_PAREN, RIGHT_PAREN,

  ATOM,

  F_EOF
};
struct Token {
  TokenType typ;
  std::string lexeme;
  std::optional<Atom> literal;
  size_t line;
  Token(TokenType typ_, std::string lexeme_, std::optional<Atom> literal_, size_t line_);
  ~Token() = default;
};

}

