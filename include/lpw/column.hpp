#ifndef LPW_COLUMN_HPP_
#define LPW_COLUMN_HPP_

#include <memory>
#include <string>

#include "lpw/common.hpp"
#include "lpw/bounds.hpp"

namespace LPW {

class LPProblem;

class Column;
typedef std::shared_ptr<Column> ColumnPtr;

class Column {
  size_t column_number_;
  BoundsPtr bounds_;
  double coefficient_;
  VariableType type_;
  std::string name_;

public:
  size_t GetColumnNumber() const { return column_number_; }
  
  BoundsPtr GetBounds() const { return bounds_; }

  VariableType GetType() const { return type_; }

  double GetCoefficient() const { return coefficient_; }
  void SetCoefficient(double coefficient)  { coefficient_ = coefficient; }

  std::string GetName() const { return name_; }
  void SetName(std::string name) { name_ = name; }

private:
  friend LPProblem;
  Column(
      size_t column_number,
      BoundsPtr bounds,
      double coefficient,
      VariableType type,
      std::string name) :
    column_number_(column_number),
    bounds_(bounds),
    coefficient_(coefficient),
    type_(type),
    name_(name)
    {}
};  // class Column

}  // namespace LPW

#endif  // LPW_COLUMN_HPP_
