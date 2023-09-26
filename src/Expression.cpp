#include <assert.h>
#include <iostream>
#include <utility>

#include "ConsCell.hpp"
#include "Expression.hpp"


namespace yisp {

SExpression::SExpression(const Atom &atom) {
  data = atom;
}

SExpression::SExpression(const std::variant<Atom, ConsCell> variant_data) : data(variant_data) {};

SExpression::SExpression(const ConsCell &consCell) : data(consCell) {}


const std::variant<Atom, ConsCell> &SExpression::get() const {
  return data;
}

std::variant<Atom, ConsCell> &SExpression::get() {
  return data;
}

size_t SExpression::size() const {
  if (std::holds_alternative<Atom>(data)) {
    return 1;
  }
  const auto &consCell = std::get<ConsCell>(data);
  if (consCell.isterminal()) {
    return 1;
  }
  const auto &cdr = consCell.cdr();
  return 1 + cdr->size();
}

void SExpression::UnsafeSetCdr(std::shared_ptr<SExpression> expr) {
  assert(std::holds_alternative<ConsCell>(data));
  std::get<ConsCell>(data).second = expr;
}

std::string SExpression::UnsafeGetStringOfStringOrIden() const {
  assert(IsAtom());
  assert (std::holds_alternative<std::string>(std::get<Atom>(data).value));

  return std::get<std::string>(std::get<Atom>(data).value);
}

bool SExpression::IsAtom() const {
  return std::holds_alternative<Atom>(data);
}

bool SExpression::IsIden() const {
  if (!IsAtom()) {
    return false;
  }
  return std::get<Atom>(data).kind == AtomKind::IDENTIFIER;
}

bool SExpression::IsNil() const {
  if (!IsAtom()) {
    return false;
  }

  return std::get<Atom>(data).kind == AtomKind::NIL;
}

SExpression operator+(const SExpression &lhs, const SExpression &rhs) {
  if (! (lhs.IsAtom() && rhs.IsAtom())) {
    std::cerr << "+ can only operate on atoms" << std::endl;
    exit(EXIT_FAILURE);
  }
  const Atom &atom1 = std::get<Atom>(lhs.get());
  const Atom &atom2 = std::get<Atom>(rhs.get());
  return atom1 + atom2;
}

SExpression operator-(const SExpression &lhs, const SExpression &rhs) {
  if (! (lhs.IsAtom() && rhs.IsAtom())) {
    std::cerr << "- can only operate on atoms" << std::endl;
    exit(EXIT_FAILURE);
  }
  const Atom &atom1 = std::get<Atom>(lhs.get());
  const Atom &atom2 = std::get<Atom>(rhs.get());
  return atom1 - atom2;
}

SExpression operator*(const SExpression &lhs, const SExpression &rhs) {
  if (! (lhs.IsAtom() && rhs.IsAtom())) {
    std::cerr << "- can only operate on atoms" << std::endl;
    exit(EXIT_FAILURE);
  }
  const Atom &atom1 = std::get<Atom>(lhs.get());
  const Atom &atom2 = std::get<Atom>(rhs.get());
  return atom1 * atom2;

}
SExpression operator==(const SExpression &lhs, const SExpression &rhs) {
  if (! (lhs.IsAtom() && rhs.IsAtom())) {
    std::cerr << "== can only operate on atoms" << std::endl;
    exit(EXIT_FAILURE);
  }
  const Atom &atom1 = std::get<Atom>(lhs.get());
  const Atom &atom2 = std::get<Atom>(rhs.get());
  return atom1 == atom2;
}



SExpression SExpression::UnsafeFirst() const {
  if (std::holds_alternative<ConsCell>(data)) {
    const auto &consCell = std::get<ConsCell>(data);
    return *consCell.first;
  } else if (std::holds_alternative<Atom>(data)) {
    std::cerr << "Cannot get the first element of an Atom" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::unreachable();
}


SExpression SExpression::UnsafeNext() const {
  if (IsAtom()) {
    std::cerr << "Cannot call next on an Atom" << std::endl;
    exit(EXIT_FAILURE);
  }

  const auto &consCell = std::get<ConsCell>(data);
  const auto &second = consCell.second;

  if (std::holds_alternative<std::shared_ptr<SExpression>>(second)) {

    return *std::get<std::shared_ptr<SExpression>>(second);
  } else if (std::holds_alternative<Atom>(second)) {
    return std::get<Atom>(second);
  }
  std::unreachable();
}

std::ostream &operator<<(std::ostream &os, const SExpression &obj) {
  const auto &data = obj.get();
  if (std::holds_alternative<Atom>(data)) {
    os << std::get<Atom>(data);
  } else if (std::holds_alternative<ConsCell>(data)) {
    os << "(";
    auto currentCell = std::get<ConsCell>(data);
    bool isFirst = true;
    while (true) {
      if (!isFirst) os << " ";
      os << *currentCell.first;
      isFirst = false;

      const auto &cdr = currentCell.second;
      if (std::holds_alternative<std::shared_ptr<SExpression>>(cdr)) {
        const auto &nextExp = *std::get<std::shared_ptr<SExpression>>(cdr);
        const auto &nextData = nextExp.get();
        if (std::holds_alternative<ConsCell>(nextData)) {
          currentCell = std::get<ConsCell>(nextData);
          continue;
        } else {
          os << " " << std::get<Atom>(nextData);
          break;
        }
      } else {
        // don't care to print CDR atoms, they should be nil
        break;
      }
    }
    os << ")";
  }
  return os;
}
}