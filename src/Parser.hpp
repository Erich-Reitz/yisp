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

Token advance(Parser &parser) ;

[[nodiscard]] bool check(const Parser &parser, TokenType typ);

Token consume(Parser &parser, TokenType typ, const std::string &message);

[[nodiscard]] bool isAtEnd(const Parser &parser);

template <typename... TokenTypes>
bool match(Parser &parser, TokenTypes... types);


std::vector<std::shared_ptr<SExpression>> parse(const std::vector<Token> &tokens);

[[nodiscard]] Token peek(const Parser &parser);

[[nodiscard]] Token previous(Parser &parser) ;

[[nodiscard]] std::shared_ptr<SExpression> expression(Parser &parser);
[[nodiscard]] yisp::Atom literal(Parser &parser) ;
[[nodiscard]] std::shared_ptr<SExpression> sExpression(Parser &parser );

}

