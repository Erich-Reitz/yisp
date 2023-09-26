#include <iostream>

#include "ConsCell.hpp"
#include "Expression.hpp"

namespace yisp {

ConsCell::ConsCell(SExpression first_, SExpression second_) {
  first = std::make_shared<SExpression>(first_);
  second = std::make_shared<SExpression>(second_);
}

ConsCell::ConsCell(std::shared_ptr<SExpression> first_) : first(std::move(first_)), second(Atom(AtomKind::NIL)) {};

ConsCell::ConsCell(std::shared_ptr<SExpression> first_, std::variant<std::shared_ptr<SExpression>, Atom> second_)
  : first(std::move(first_)), second(std::move(second_)) {}


bool ConsCell::isterminal() const {
  if (std::holds_alternative<Atom>(second)) {
    return true;
  }
  return false;
}

std::shared_ptr<SExpression> ConsCell::cdr() const {
  if (isterminal()) {
    std::cerr << "attempting to get CDR of cell where CDR is atom" << std::endl;
    exit(EXIT_FAILURE);
  }
  return std::get<std::shared_ptr<SExpression>>(second);
}

std::ostream &operator<<(std::ostream &os, const ConsCell &cell) {
  os << "(";
  os << *cell.first;

  const auto &cdr = cell.second;
  if (std::holds_alternative<std::shared_ptr<SExpression>>(cdr)) {
    const auto &nextExp = *std::get<std::shared_ptr<SExpression>>(cdr);
    os << " " << nextExp;
  } else {
    os << " " << std::get<Atom>(cdr);
  }
  os << ")";
  return os;
}

}
