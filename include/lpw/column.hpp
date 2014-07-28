#ifndef LPW_COLUMN_HPP_
#define LPW_COLUMN_HPP_

#include <memory>
#include <string>

#include "lpw/common.hpp"

namespace LPW {

class Column;
typedef std::shared_ptr<Column> ColumnPtr;

class Column {
  size_t column_number_;
  BoundsPtr bounds_;
  double coefficient_;
  std::string name_;

public:
  size_t ColumnNumber() const { return column_number_; }

  double Coefficient() const { return coefficient_; }
  double& Coefficient()  { return coefficient_; }

  std::string Name() const { return name_; }
  std::string& Name() { return name_; }

private:
  friend ColumnPtr std::make_shared<Column>(size_t, BoundsPtr, double, std::string);
  Column(
      size_t column_number,
      BoundsPtr bounds,
      double coefficient,
      std::string name) :
    column_number_(column_number),
    bounds_(bounds),
    coefficient_(coefficient),
    name_(name)
    {}
};  // class Column


}  // namespace LPW

#endif  // LPW_COLUMN_HPP_
