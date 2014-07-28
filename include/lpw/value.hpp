#ifndef LPW_VALUE_HPP_
#define LPW_VALUE_HPP_

#include <memory>
#include <string>

#include "lpw/column.hpp"

namespace LPW {

class LPProblem;

class Value;
typedef std::shared_ptr<Value> ValuePtr;

class Value {
  const RowPtr row_ptr_;
  const ColumnPtr column_ptr_;
  double value_;

public:
  const RowPtr GetRow() const { return row_ptr_; }

  const ColumnPtr GetColumn() const { return column_ptr_; }

  double GetValue() const { return value_; }
  void SetValue(double value) { value_ = value; }

private:
  friend LPProblem;
  Value(RowPtr row_ptr, ColumnPtr column_ptr, double value) :
    row_ptr_(row_ptr),
    column_ptr_(column_ptr),
    value_(value)
    {}
};  // class Value

}  // namespace LPW

#endif  // LPW_VALUE_HPP_
