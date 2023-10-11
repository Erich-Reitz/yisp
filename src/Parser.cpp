#include <iostream>
#include <memory>
#include <variant>

#include "ConsCell.hpp"
#include "Parser.hpp"
#include "Expression.hpp"

namespace yisp::parser {
[[nodiscard]] static std::shared_ptr<SExpression> sExpression(Parser &parser) ;

Parser::Parser(const std::vector<Token> &tokens_) : tokens(tokens_), current(0) {};


[[nodiscard]] static Token peek(const Parser &parser) {
  return parser.tokens.at(parser.current);
}

[[nodiscard]] static  bool isAtEnd(const Parser &parser) {
  return peek(parser).typ == TokenType::F_EOF;
}

[[nodiscard]] static  Token previous(Parser &parser) {
  return parser.tokens.at(parser.current -1);
}

[[nodiscard]] static bool check(const Parser &parser, const TokenType typ) {
  if (isAtEnd(parser)) {
    return false;
  }

  return peek(parser).typ == typ;
}

static Token advance(Parser &parser) {
  if (!isAtEnd(parser)) {
    parser.current += 1;
  }
  return previous(parser);
}

static Token consume(Parser &parser, const TokenType typ, const std::string &message) {
  if (check(parser, typ)) {
    return advance(parser);
  }
  std::cerr << "parse error: " << message << std::endl;
  exit(EXIT_FAILURE);
}

template <typename... TokenTypes>
static bool match(Parser &parser, TokenTypes... types) {
  TokenType typeArray[] = { types... };
  for (TokenType type : typeArray) {
    if (check(parser, type)) {
      advance(parser);
      return true;
    }
  }
  return false;
}


[[nodiscard]] static yisp::Atom  literal(Parser &parser) {
  if (match(parser, TokenType::ATOM)) {
    const Token lit = previous(parser);
    return lit.literal.value();
  }

  return Atom(AtomKind::NIL);
}

[[nodiscard]] static std::shared_ptr<SExpression> expression(Parser &parser) {
  if (match(parser, TokenType::LEFT_PAREN)) {
    return sExpression(parser);
  }
  return std::make_shared<SExpression>(literal(parser));
}

[[nodiscard]] static std::shared_ptr<SExpression> sExpression(Parser &parser) {
  if (match(parser, TokenType::RIGHT_PAREN)) {
    return std::make_shared<SExpression>(Atom(AtomKind::NIL));
  }
  auto sentinel = std::make_shared<SExpression>(ConsCell{nullptr, Atom(AtomKind::NIL)});
  auto currentCell = sentinel;

  while (!check(parser, TokenType::RIGHT_PAREN)) {
    if (isAtEnd(parser)) {
      std::cerr << "parse error: unmatched parenthesis" << std::endl;
      exit(EXIT_FAILURE);
    }

    auto expr = expression(parser);
    auto newCell = std::make_shared<SExpression>(ConsCell{expr, Atom(AtomKind::NIL)});

    std::get<yisp::ConsCell>(currentCell->get()).second = newCell;

    currentCell = newCell;
  }

  consume(parser, TokenType::RIGHT_PAREN, "Expected )");
  auto &sentinelNext = std::get<ConsCell>(sentinel->get()).second;
  if (std::holds_alternative<std::shared_ptr<SExpression>>(sentinelNext)) {
    return std::get<std::shared_ptr<SExpression>>(sentinelNext);
  }

  return nullptr;
}




std::vector<std::shared_ptr<SExpression>> parse(const std::vector<Token> &tokens) {
  auto parser = Parser(tokens);
  std::vector<std::shared_ptr<SExpression>> expressions;
  while (!isAtEnd(parser)) {
    const auto &expr = expression(parser);
    expressions.push_back(expr);
  }
  return expressions;
}
}

