
#include <iostream>
#include <vector>



#include "lexer.hpp"
#include "Scanner.hpp"
#include "Token.hpp"



namespace yisp::lexer {
void seenString(Scanner &scanner);
void seenNumber(Scanner &scanner);
void seenIdentifier(Scanner &scanner);


void seenNumber(Scanner &scanner) {
  while (isdigit(peek(scanner))) {
    advance(scanner);
  }

  if (peek(scanner) == '.' && isdigit(peekNext(scanner))) {
    advance(scanner);

    while (isdigit(peek(scanner))) {
      advance(scanner);
    }
  }

  const std::string numText = scanner.source.substr(scanner.start, scanner.current - scanner.start);
  addToken(scanner, TokenType::ATOM, Atom(AtomKind::NUMBER, std::stof(numText)));
}


void seenIdentifier(Scanner &scanner) {
  while (isalnum(peek(scanner)) || peek(scanner) == '?') {
    advance(scanner);
  }

  const std::string text = scanner.source.substr(scanner.start, scanner.current - scanner.start);
  const auto literal = Atom(AtomKind::IDENTIFIER, text) ;
  addToken(scanner, TokenType::ATOM, literal);

}

void seenString(Scanner &scanner) {
  while (peek(scanner) != '\"' && !isAtEnd(scanner)) {
    if (peek(scanner) == '\n') {
      scanner.line += 1;
    }
    advance(scanner);
  }
  if (isAtEnd(scanner)) {
    std::cerr << scanner.line << "Unterminated string." << std::endl;
    exit(EXIT_FAILURE);
  }
  advance(scanner);
  const auto value = scanner.source.substr(scanner.start + 1, (scanner.current - scanner.start - 2)) ;
  const auto literal = Atom(AtomKind::STRING, value) ;
  addToken(scanner, TokenType::ATOM, literal);
}

void scanToken(Scanner &scanner) {
  char c = advance(scanner);
  switch (c) {
  case '(':
    addToken(scanner, TokenType::LEFT_PAREN);
    break;
  case ')':
    addToken(scanner, TokenType::RIGHT_PAREN);
    break;
//   case '\'':
//     addToken(scanner, TokenType::QUOTE);
//     break;
  case ';':
    while ((peek(scanner) != '\n') && (isAtEnd(scanner) == false)) {
      advance(scanner) ;
    }
    break;
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    scanner.line++;
    break;
  case '"':
    seenString(scanner);
    break;
  default:          // handle negative numbers
    if (isdigit(c) || (c == '-' && isdigit(peek(scanner)))) {
      seenNumber(scanner);
    } else if (isalpha(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '<' || c == '>' || c == '=') {
      seenIdentifier(scanner);
    } else {
      std::cerr << scanner.line << "Unexpected character" << std::endl;
      exit(EXIT_FAILURE);
    }

    break;
  }
}

std::vector<Token> lex(const std::string &text) {
  Scanner scanner =  Scanner(text);
  while (!isAtEnd(scanner))  {
    scanner.start = scanner.current;
    scanToken(scanner);
  }
  addToken(scanner, TokenType::F_EOF);
  return scanner.tokens;
}
}
