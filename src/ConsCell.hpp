#pragma once
#include <memory>
#include <variant>
#include <ostream>
#include "Atom.hpp"

namespace yisp {
class SExpression;

class ConsCell {
 public:
  ConsCell(std::shared_ptr<SExpression> first_);
  ConsCell(SExpression first_, SExpression second_);
  ConsCell(std::shared_ptr<SExpression> first_, std::variant<std::shared_ptr<SExpression>, Atom> second_);
  std::shared_ptr<SExpression> cdr() const;
  bool isterminal() const;
  std::shared_ptr<SExpression> first;
  std::variant<std::shared_ptr<SExpression>, Atom> second;

  friend std::ostream &operator<<(std::ostream &os, const ConsCell &cell);
};

}
