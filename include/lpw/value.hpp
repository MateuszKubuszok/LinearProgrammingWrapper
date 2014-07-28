#ifndef LPW_VALUE_HPP_
#define LPW_VALUE_HPP_

#include <memory>
#include <string>

#include "lpw/Value.hpp"
#include "lpw/column.hpp"

namespace LPW {

class Value;
typedef std::shared_ptr<Value> RowPtr;

class Value {
  const RowPtr row_ptr_;
  const ColumnPtr column_ptr_;
  double value_;

public:
  const RowPtr Row() const {
    return row_ptr_;
  }

  const ColumnPtr Column() const {
    return column_ptr_;
  }

  double Value() const {
    return value_;
  }
  double& Value() {
    return value_;
  }

private:
  friend RowPtr std::make_shared<Value>(RowPtr, ColumnPtr, double);
  Value(RowPtr row_ptr, ColumnPtr column_ptr, double value) :
    row_ptr_(row_ptr),
    column_ptr_(column_ptr),
    value_(value)
    {}
};  // class Value


}  // namespace LPW

#endif  // LPW_VALUE_HPP_
