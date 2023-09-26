
#include <memory>
#include "Builtins.hpp"
#include "InterpreterObj.hpp"


namespace yisp::interpreter {

InterpreterObj::InterpreterObj() {
  functions = {
    // required builtins for project
    {"define", &builtins::Define},
    {"set", &builtins::Set},

    {"+", &builtins::Plus},
    {"-", &builtins::Minus},
    {"*", &builtins::Star},
    {"/", &builtins::Slash},
    {"=", &builtins::Equals},
    {"<", &builtins::Less},
    {">", &builtins::Greater},

    {"cons", &builtins::Cons},
    {"car", &builtins::Car},
    {"cdr", &builtins::Cdr},

    {"NUMBER?", &builtins::IsNumber},
    {"SYMBOL?", &builtins::IsSymbol},
    {"LIST?", &builtins::IsList},
    {"NIL?", &builtins::IsNil},
    {"AND?", &builtins::And},
    {"OR?", &builtins::Or},

    // challenges
    {"list", &builtins::List},
  };
}

}

