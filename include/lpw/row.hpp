#ifndef LPW_ROW_HPP_
#define LPW_ROW_HPP_

#include <memory>
#include <string>

#include "lpw/common.hpp"
#include "lpw/bounds.hpp"

namespace LPW {

class LPProblem;

class Row;
typedef std::shared_ptr<Row> RowPtr;

class Row {
  size_t row_number_;
  BoundsPtr bounds_;
  std::string name_;

public:
  size_t GetRowNumber() const { return row_number_; }

  BoundsPtr GetBounds() const { return bounds_; }

  std::string GetName() const { return name_; }
  void SetName(std::string name) { name_ = name; }

private:
  friend LPProblem;
  Row(size_t row_number, BoundsPtr bounds, std::string name) :
    row_number_(row_number),
    bounds_(bounds),
    name_(name)
    {}
};  // class Row

}  // namespace LPW

#endif  // LPW_ROW_HPP_
