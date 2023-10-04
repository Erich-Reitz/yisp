#include <cassert>
#include <iostream>

#include "Builtins.hpp"
#include "interpreter.hpp"

namespace yisp::interpreter::builtins {


#define CHECK_ARITY(FUNC_NAME, ARGS, EXPECTED_ARITY) \
    if((ARGS).size() != (EXPECTED_ARITY)) { \
        throw std::runtime_error(FUNC_NAME " requires exactly " #EXPECTED_ARITY " arguments"); \
    }

#define CHECK_MIN_ARITY(FUNC_NAME, ARGS, MIN_EXPECTED_ARITY) \
    if((ARGS).size() < (MIN_EXPECTED_ARITY)) { \
        throw std::runtime_error(FUNC_NAME " requires at least " #MIN_EXPECTED_ARITY " arguments"); \
    }


SExpression Plus(InterpreterObj &interpreter, const SExpression &arg) {
  SExpression sum = Atom(AtomKind::NUMBER, 0.0f);
  for (const auto &current : arg) {
    sum = sum + evaluate(interpreter, current);
  }
  return sum;
}

SExpression Minus(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_MIN_ARITY("-", arg, 1);
  auto it =arg.begin();
  yisp::SExpression result = evaluate(interpreter, *it);
  ++it;
  for (; it != arg.end(); ++it) {
    result = result - evaluate(interpreter, *it);
  }

  return result;
}


SExpression Star(InterpreterObj &interpreter, const SExpression &arg) {
  SExpression product = Atom(AtomKind::NUMBER, 1.0f);
  for (const auto &current : arg) {
    product = product * evaluate(interpreter, current);
  }
  return product;
}

SExpression Slash(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY("/", arg, 2);
  auto it = arg.begin();
  const auto &arg1 = evaluate(interpreter, *it);
  ++it;
  const auto &arg2 = evaluate(interpreter, *it);
  assert(arg1.IsAtom() && arg2.IsAtom());
  return std::get<Atom>(arg1.get()) / std::get<Atom>(arg2.get());
}


SExpression Equals(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY("=", arg, 2);
  auto it = arg.begin();
  const auto &arg1 = evaluate(interpreter, *it);
  ++it;
  const auto &arg2 = evaluate(interpreter, *it);
  assert(arg1.IsAtom() && arg2.IsAtom());
  return std::get<Atom>(arg1.get()) == std::get<Atom>(arg2.get());
}


SExpression Less(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY("<", arg, 2);
  auto it = arg.begin();
  const auto &arg1 = evaluate(interpreter, *it);
  ++it;
  const auto &arg2 = evaluate(interpreter, *it);
  assert(arg1.IsAtom() && arg2.IsAtom());
  return std::get<Atom>(arg1.get()) < std::get<Atom>(arg2.get());
}

SExpression Greater(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY(">", arg, 2);
  auto it = arg.begin();
  const auto &arg1 = evaluate(interpreter, *it);
  ++it;
  const auto &arg2 = evaluate(interpreter, *it);
  assert(arg1.IsAtom() && arg2.IsAtom());
  return std::get<Atom>(arg1.get()) > std::get<Atom>(arg2.get());
}

SExpression And(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY("AND", arg, 2);
  auto it = arg.begin();
  const auto &unevalutedArg1 = *it;
  ++it;
  const auto &unevalutedArg2 = *it;
  if (evaluate(interpreter, unevalutedArg1).IsNil() || evaluate(interpreter, unevalutedArg2).IsNil()) {
    return Atom(AtomKind::NIL);
  }

  return Atom(AtomKind::TRUE);
}


SExpression Or(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY("OR", arg, 2);
  auto it = arg.begin();
  const auto &unevalutedArg1 = *it;
  ++it;
  const auto &unevalutedArg2 = *it;
  if (evaluate(interpreter, unevalutedArg1).IsNil() == false) {
    return Atom(AtomKind::TRUE);
  }

  if (evaluate(interpreter, unevalutedArg2).IsNil() == false) {
    return Atom(AtomKind::TRUE);
  }

  return Atom(AtomKind::NIL);
}


SExpression IsNil(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY("NIL?", arg, 1);
  auto it = arg.begin();
  if (evaluate(interpreter, *it).IsNil()) {
    return Atom(AtomKind::TRUE);
  }

  return Atom(AtomKind::NIL);
}



SExpression Define(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY("define", arg, 3);
  auto it = arg.begin();
  auto functionName = (*it).UnsafeGetStringOfStringOrIden();
  ++it;
  auto paramsExpr = *it;
  ++it;
  auto body = *it;
  // pass interpreter by value to userdefined function, get scoping for free?
  interpreter.functions[functionName] = [paramsExpr, body](InterpreterObj interp, const SExpression &args) -> SExpression {
    auto paramIt = paramsExpr.begin();
    auto argIt = args.begin();

    while (paramIt != paramsExpr.end() && argIt != args.end()) {
      const std::string paramName = (*paramIt).UnsafeGetStringOfStringOrIden();
      const SExpression argValue = evaluate(interp, *argIt);
      interp.values[paramName] = argValue;
      ++paramIt;
      ++argIt;
    }

    if (paramIt != paramsExpr.end() || argIt != args.end()) {
      throw std::runtime_error("Function called with incorrect number of arguments");
    }

    return evaluate(interp, body);
  };

  return Atom(AtomKind::IDENTIFIER, functionName);
}

SExpression Set(InterpreterObj &interpreter, const SExpression &arg) {
  const auto varname = arg.UnsafeFirst().UnsafeGetStringOfStringOrIden();
  const auto initalizer = arg.UnsafeNext();
  interpreter.values[varname] = evaluate(interpreter, initalizer);
  return Atom(AtomKind::IDENTIFIER, varname);
}


SExpression List(InterpreterObj &interpreter, const SExpression &arg) {
  if (arg.IsNil()) {
    return Atom(AtomKind::NIL);
  }

  auto it = arg.begin();
  auto evaluated = evaluate(interpreter, *it);
  auto head = std::make_shared<SExpression>(ConsCell(std::make_shared<SExpression>(evaluated)));
  auto current = head;
  ++it;

  for (; it != arg.end(); ++it) {
    evaluated = evaluate(interpreter, *it);
    auto newConsCell = std::make_shared<SExpression>(ConsCell(std::make_shared<SExpression>(evaluated)));
    current->UnsafeSetCdr(newConsCell);
    current = newConsCell;
  }

  return *head;
}


SExpression IsNumber(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY("NUMBER?", arg, 1);
  const auto &evaluatedArg = evaluate(interpreter, arg);
  const auto &data = evaluatedArg.get();
  if (std::holds_alternative<Atom>(data)) {
    const auto &atom = std::get<Atom>(data);
    if (atom.kind == AtomKind::NUMBER) {
      return Atom(AtomKind::TRUE);
    }
    return Atom(AtomKind::NIL);
  }

  return Atom(AtomKind::NIL);
}

SExpression IsList(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY("LIST?", arg, 1);
  const auto &evaluatedArg = evaluate(interpreter, arg);
  const auto &data = evaluatedArg.get();
  if (std::holds_alternative<ConsCell>(data)) {
    return Atom(AtomKind::TRUE);
  }

  return Atom(AtomKind::NIL);
}

SExpression IsSymbol(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY("SYMBOL?", arg, 1);
  const auto &data = arg.get();
  if (std::holds_alternative<Atom>(data)) {
    const auto &atom = std::get<Atom>(data);
    if (atom.kind == AtomKind::IDENTIFIER) {
      return Atom(AtomKind::TRUE);
    }
    return Atom(AtomKind::NIL);
  } else if (std::holds_alternative<ConsCell>(data)) {
    const auto cell = std::get<ConsCell>(data);
    if (cell.isterminal() && cell.first.get()->IsIden()) {
      return Atom(AtomKind::TRUE);
    }
  }

  return Atom(AtomKind::NIL);
}

SExpression Cons(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY("cons", arg, 2);
  auto it = arg.begin();
  const auto &unevaluatedArg1 = *it;
  ++it;
  const auto &unevaluatedArg2 = *it;
  return ConsCell(evaluate(interpreter, unevaluatedArg1), evaluate(interpreter, unevaluatedArg2));
}

SExpression Car(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_ARITY("car", arg, 1);
  return evaluate(interpreter, arg).UnsafeFirst();
}

SExpression Cdr(InterpreterObj &interpreter, const SExpression &arg) {
  return evaluate(interpreter, arg).UnsafeNext();
}


SExpression Cond(InterpreterObj &interpreter, const SExpression &arg) {
  CHECK_MIN_ARITY("cond", arg, 1);
  for (const auto &conditionValuePair : arg) {
    const auto &conditionalExpr = conditionValuePair.UnsafeFirst();
    const auto &resultExpr = conditionValuePair.UnsafeNext();
    const auto conditionalResult = evaluate(interpreter, conditionalExpr);
    if (!conditionalResult.IsNil()) {
      return evaluate(interpreter, resultExpr);
    }
  }
  return Atom(AtomKind::NIL);
}





}