#pragma once

#include <ostream>
#include <string>
#include <sstream>
#include <variant>

#include "Atom.hpp"

namespace yisp {

enum class AtomKind {
  NIL,
  TRUE,
  NUMBER,
  STRING,
  IDENTIFIER
};

class Atom {
 public:

  Atom() = default;

  Atom(const Atom &other)
    : kind(other.kind), value(other.value) {}

  Atom &operator=(const Atom &other) {
    if (this == &other) {
      return *this;
    }
    this->kind = other.kind;
    this->value = other.value;
    return *this;
  }
  explicit  Atom(AtomKind kind_);
  Atom(AtomKind kind_, std::variant<float, std::string> value);
  friend Atom operator+(const Atom &lhs, const Atom &rhs);
  friend Atom operator-(const Atom &lhs, const Atom &rhs);
  friend Atom operator*(const Atom &lhs, const Atom &rhs);
  friend Atom operator/(const Atom &lhs, const Atom &rhs);
  friend Atom operator<(const Atom &lhs, const Atom &rhs);
  friend Atom operator>(const Atom &lhs, const Atom &rhs);
  friend Atom operator==(const Atom &lhs, const Atom &rhs);

  AtomKind kind;
  std::variant<float, std::string> value;


  friend std::ostream &operator<<(std::ostream &os, const Atom &Atom);
};


inline std::ostream &operator<<(std::ostream &os, const Atom &Atom) {
  if (Atom.kind == AtomKind::NIL) {
    os << "nil";
    return os;
  }

  if (Atom.kind == AtomKind::TRUE) {
    os << "t";
    return os;
  }

  if (Atom.kind == AtomKind::STRING) {
    os << "\"" << std::get<std::string>(Atom.value) << "\"";
    return os;
  }

  std::visit([&os](auto &&arg) {
    os << arg;
  }, Atom.value);


  return os;
}


}
