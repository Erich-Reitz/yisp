#include <cassert>
#include <iostream>
#include <variant>


#include "Atom.hpp"
namespace yisp {

Atom::Atom(AtomKind kind_) : kind(kind_) {
  // can't think of a reason to construct an atom of these types without initializing the value
  assert (kind_ != AtomKind::NUMBER && kind_ != AtomKind::STRING);
}

Atom::Atom(AtomKind kind_, std::variant<float, std::string> value_) : kind(kind_), value(std::move(value_)) {
}



#define DEFINE_NUMERICAL_ATOM_OPERATOR(OP, RESULT_TYPE, EXPRESSION) \
Atom operator OP (const Atom &lhs, const Atom &rhs) { \
    if (std::holds_alternative<float>(lhs.value) && std::holds_alternative<float>(rhs.value)) { \
        float a = std::get<float>(lhs.value); \
        float b = std::get<float>(rhs.value); \
        return Atom(RESULT_TYPE, EXPRESSION); \
    } \
    std::cerr << "Invalid types for " #OP " operation."; \
    exit(EXIT_FAILURE);  \
}

#define DEFINE_COMPARISION_ATOM_OPERATOR(OP,  EXPRESSION) \
Atom operator OP (const Atom &lhs, const Atom &rhs) { \
    if (std::holds_alternative<float>(lhs.value) && std::holds_alternative<float>(rhs.value)) { \
        float a = std::get<float>(lhs.value); \
        float b = std::get<float>(rhs.value); \
        \
        if (EXPRESSION) {   \
          return Atom(AtomKind::TRUE);                  \
        }                   \
        return Atom(AtomKind::NIL);      \
    } \
    std::cerr << "Invalid types for " #OP " operation."; \
    exit(EXIT_FAILURE);  \
}



DEFINE_NUMERICAL_ATOM_OPERATOR(+, AtomKind::NUMBER, a + b)
DEFINE_NUMERICAL_ATOM_OPERATOR(-, AtomKind::NUMBER, a - b)
DEFINE_NUMERICAL_ATOM_OPERATOR(*, AtomKind::NUMBER, a *b)
DEFINE_NUMERICAL_ATOM_OPERATOR(/, AtomKind::NUMBER, a / b)
DEFINE_COMPARISION_ATOM_OPERATOR(<, a < b)
DEFINE_COMPARISION_ATOM_OPERATOR(>,  a > b)
#undef DEFINE_ATOM_OPERATOR

Atom operator==(const Atom &lhs, const Atom &rhs) {
  const bool res = std::visit([](const auto& a, const auto& b) -> bool {
    if constexpr (std::is_same_v<decltype(a), decltype(b)>) {
      return a == b;
    } else {
      return false;
    }
  }, lhs.value, rhs.value);
  if (res) {
    return Atom(AtomKind::TRUE);
  }

  return Atom(AtomKind::NIL);
}


}
