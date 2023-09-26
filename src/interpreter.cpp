#include <cassert>
#include <iostream>
#include <ranges>
#include <utility>
#include <variant>
#include <vector>

#include "Atom.hpp"
#include "Builtins.hpp"
#include "ConsCell.hpp"
#include "Expression.hpp"
#include "interpreter.hpp"



namespace yisp::interpreter {
SExpression evaluate(InterpreterObj &interpreter, const Atom &atm) ;
SExpression evaluate(InterpreterObj &interpreter, const ConsCell &conscell);


SExpression evaluate(InterpreterObj &interpreter, const Atom &atm) {
  if (atm.kind == AtomKind::IDENTIFIER) {
    const auto key = std::get<std::string>(atm.value);
    if (interpreter.values.find(key) != interpreter.values.end()) {
      return interpreter.values[std::get<std::string>(atm.value)] ;
    }
    const auto err_string = "Undefined identifier: " + key ;
    throw std::runtime_error(err_string.c_str());
  }
  return atm;
}

SExpression evaluate(InterpreterObj &interpreter, const ConsCell &conscell) {
  const auto &car = *conscell.first.get();
  // if we have a conscell like (5 nil), (a nil), ((list 1 2 3) nil) we just want to return the value
  if(conscell.isterminal()) {
    const auto sexpr = SExpression(car);
    return evaluate(interpreter, sexpr);
  }
  const auto cdr = *std::get<std::shared_ptr<SExpression>>(conscell.second);
  const auto func_name = car.UnsafeGetStringOfStringOrIden();

  auto it = interpreter.functions.find(func_name);
  if(it != interpreter.functions.end()) {
    return it->second(interpreter, cdr);
  }

  const auto err_string = "Undefined identifier: " + func_name ;
  throw std::runtime_error(err_string.c_str());
}

SExpression evaluate(InterpreterObj &interpreter, const SExpression &expression) {
  return std::visit([&interpreter](const auto &data) -> SExpression {
    return evaluate(interpreter, data);
  }, expression.get());
}

int interpret(std::vector<std::shared_ptr<SExpression>> expressions) {
  InterpreterObj interpreter = InterpreterObj();

  for (const auto &expression : expressions) {
    const auto result = evaluate(interpreter, *expression.get());

    std::cout << result << std::endl;
  }
  return 0;
}


}


