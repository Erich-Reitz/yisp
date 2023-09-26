#pragma once


#include <vector>

#include "Expression.hpp"
#include "InterpreterObj.hpp"

namespace yisp::interpreter {
SExpression evaluate(InterpreterObj &interpreter, const SExpression &expression);
void interpret(std::vector<std::shared_ptr<SExpression>> expressions);
}
