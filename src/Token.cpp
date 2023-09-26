#include <iostream>

#include "Atom.hpp"
#include "Token.hpp"


namespace yisp {
Token::Token(TokenType typ_, std::string lexeme_, std::optional<Atom> literal_, size_t line_) : typ(typ_), lexeme(std::move(lexeme_)),
  literal(std::move(literal_)), line(line_) {}
}
