#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>


#include "Expression.hpp"

namespace yisp::interpreter {
struct InterpreterObj {

  InterpreterObj();
  std::unordered_map<std::string, std::function<yisp::SExpression(InterpreterObj &, const yisp::SExpression &)>> functions;
  std::unordered_map<std::string, SExpression> values;
};
}
