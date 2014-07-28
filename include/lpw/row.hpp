#ifndef LPW_ROW_HPP_
#define LPW_ROW_HPP_

#include <memory>
#include <string>

#include "lpw/common.hpp"

namespace LPW {

class Row;
typedef std::shared_ptr<Row> RowPtr;

class Row {
  size_t row_number_;
  BoundsPtr bounds_;
  std::string name_;

public:
  size_t RowNumber() const { return row_number_; }

  std::string Name() const { return name_; }
  std::string& Name() { return name_; }

private:
  friend RowPtr std::make_shared<Row>(size_t, BoundsPtr, std::string);
  Row(size_t row_number, BoundsPtr bounds, std::string name) :
    row_number_(row_number),
    bounds_(bounds),
    name_(name)
    {}
};  // class Row

}  // namespace LPW

#endif  // LPW_ROW_HPP_
