#pragma once


#include <vector>

#include "Expression.hpp"
#include "InterpreterObj.hpp"

namespace yisp::interpreter {
SExpression evaluate(InterpreterObj &interpreter, const SExpression &expression);
int interpret(std::vector<std::shared_ptr<SExpression>> expressions);
}
