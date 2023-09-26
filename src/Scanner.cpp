#include <cassert>
#include <string>

#include "Token.hpp"
#include "Scanner.hpp"



namespace yisp::lexer {

bool isAtEnd(const Scanner &scanner) {
  return scanner.current >= scanner.source.length();
}

char advance(Scanner &scanner) {
  assert (scanner.current < scanner.source.size()) ;
  char result = scanner.source.at(scanner.current);
  scanner.current++;
  return result;
}

void addToken(Scanner &scanner, TokenType typ, std::optional<Atom> literal) {
  std::string lexemeText = "EOF";
  if (typ != TokenType::F_EOF) {
    lexemeText = scanner.source.substr(scanner.start, scanner.current - scanner.start);
  }

  Token token(typ, lexemeText, std::move(literal), scanner.line);
  scanner.tokens.push_back(token);
}

void addToken(Scanner &scanner, TokenType typ) {
  addToken(scanner, typ, std::nullopt);
}

char peek(const Scanner &scanner) {
  if (isAtEnd(scanner)) {
    return '\n';
  }
  return scanner.source.at(scanner.current);
}

char peekNext(const Scanner &scanner) {
  if (scanner.current + 1 >= scanner.source.length()) {
    return '\0';
  }
  return scanner.source.at(scanner.current + 1);
}


}

