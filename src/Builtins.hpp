#pragma once

#include "Expression.hpp"
#include "InterpreterObj.hpp"

namespace yisp::interpreter::builtins {
// operators
SExpression Less(InterpreterObj &interpreter, const SExpression &arg) ;
SExpression Greater(InterpreterObj &interpreter, const SExpression &arg) ;
SExpression Plus(InterpreterObj &interpreter, const SExpression &arg) ;
SExpression Minus(InterpreterObj &interpreter, const SExpression &arg) ;
SExpression Star(InterpreterObj &interpreter, const SExpression &arg) ;
SExpression Slash(InterpreterObj &interpreter, const SExpression &arg);
SExpression Equals(InterpreterObj &interpreter, const SExpression &arg);
// conditionals
SExpression And(InterpreterObj &interpreter, const SExpression &arg) ;
SExpression Or(InterpreterObj &interpreter, const SExpression &arg) ;

// unary
SExpression IsNumber(InterpreterObj &interpreter, const SExpression &arg);
SExpression IsList(InterpreterObj &interpreter, const SExpression &arg);
SExpression IsSymbol(InterpreterObj &interpreter, const SExpression &arg);
SExpression IsNil(InterpreterObj &interpreter, const SExpression &arg);

// lisp
SExpression Define(InterpreterObj &interpreter, const SExpression &arg) ;
SExpression Set(InterpreterObj &interpreter, const SExpression &arg) ;
SExpression List(InterpreterObj &interpreter, const SExpression &arg) ;
SExpression Car(InterpreterObj &interpreter, const SExpression &arg);
SExpression Cdr(InterpreterObj &interpreter, const SExpression &arg);
SExpression Cons(InterpreterObj &interpreter, const SExpression &arg);
SExpression Cond(InterpreterObj &interpreter, const SExpression &arg);
}
