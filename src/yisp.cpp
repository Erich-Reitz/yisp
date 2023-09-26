#include "filereads.hpp"
#include "lexer.hpp"
#include "interpreter.hpp"
#include "Parser.hpp"
#include "yisp.hpp"

namespace yisp {

int run(const std::string &contents) {
  const auto tokens = lexer::lex(contents);
  const auto expressions = parser::parse(tokens);
  interpreter::interpret(expressions);
  return 0;
}

int runFile(const std::string &sourceFile) {
  const auto fileContents = m_std::readFile(sourceFile);
  return run(fileContents);
}
}
