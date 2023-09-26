#pragma once

#include <memory>
#include <variant>
#include <vector>
#include <ostream>

#include "Atom.hpp"
#include "ConsCell.hpp"



namespace yisp {
class ConsCell;
class SExpression {
 public:
  SExpression() = default;
  SExpression(const std::variant<Atom, ConsCell> variant_data);
  SExpression(const Atom &atom);
  SExpression(const ConsCell &consCell);

  SExpression UnsafeFirst() const;
  SExpression UnsafeNext() const;
  std::string UnsafeGetStringOfStringOrIden() const;

  size_t size() const;

  void UnsafeSetCdr(std::shared_ptr<SExpression> expr) ;

  const std::variant<Atom, ConsCell> &get() const;
  std::variant<Atom, ConsCell> &get();

  bool IsAtom() const;
  bool IsIden() const;
  bool IsNil() const;


  friend SExpression operator+(const SExpression &lhs, const SExpression &rhs);
  friend SExpression operator-(const SExpression &lhs, const SExpression &rhs);
  friend SExpression operator*(const SExpression &lhs, const SExpression &rhs);
  friend SExpression operator==(const SExpression &lhs, const SExpression &rhs);



  friend std::ostream &operator<<(std::ostream &os, const SExpression &obj);
  class Iterator {
   public:
    Iterator(const SExpression *sexp) : current(sexp) {}

    const SExpression &operator*() const {
      const auto &data = current->get();
      if (std::holds_alternative<yisp::ConsCell>(data)) {
        return *std::get<yisp::ConsCell>(data).first;
      }
      throw std::runtime_error("Attempt to dereference non-cons-cell");
    }

    Iterator &operator++() {
      const auto &data = current->get();
      if (std::holds_alternative<yisp::ConsCell>(data)) {
        const auto &cdr = std::get<yisp::ConsCell>(data).second;
        if (std::holds_alternative<std::shared_ptr<SExpression>>(cdr)) {
          current = std::get<std::shared_ptr<SExpression>>(cdr).get();
        } else {
          current = nullptr;
        }
      } else {
        current = nullptr;
      }
      return *this;
    }

    bool operator!=(const Iterator &other) const {
      return current != other.current;
    }
    bool operator==(const Iterator &other) const {
      return current == other.current;
    }

   private:
    const SExpression *current;
  };


  Iterator begin() const {
    return Iterator(this);
  }

  Iterator end() const {
    return Iterator(nullptr);
  }
 private:
  std::variant<Atom, ConsCell> data;

};

}
