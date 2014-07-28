#ifndef LPW_LP_PROBLEM_HPP_
#define LPW_LP_PROBLEM_HPP_

#include <memory>
#include <vector>

#include "lpw/common.hpp"
#include "lpw/bounds.hpp"
#include "lpw/row.hpp"
#include "lpw/column.hpp"
#include "lpw/value.hpp"

namespace LPW {

class LPProblem {
  CostFunctionGoal goal_;
  std::string name_;

  std::vector<RowPtr> rows_;
  std::vector<ColumnPtr> columns_;
  std::vector<ValuePtr> values_;

public:
  static std::unique_ptr<LPProblem> CreateUnique(
    ImplementationType impl = ImplementationType::Default,
    CostFunctionGoal goal = CostFunctionGoal::Minimize,
    std::string name = "");
  static std::shared_ptr<LPProblem> CreateShared(
    ImplementationType impl = ImplementationType::Default,
    CostFunctionGoal goal = CostFunctionGoal::Minimize,
    std::string name = "");

  CostFunctionGoal Goal() const {
    return goal_;
  }
  CostFunctionGoal& Goal() {
    return goal_;
  }

  std::string Name() const {
    return name_;
  }
  std::string& Name() {
    return name_;
  }

  RowPtr CreateRow(BoundsPtr bounds, std::string name = "");

  ColumnPtr CreateColumn(BoundsPtr bounds, double coefficient = 0.0, std::string name = "");

  ValuePtr AddValue(RowPtr row, ColumnPtr column, double value = 0.0);

  Solution Solve() const = 0;

protected:
  LPProblem(CostFunctionGoal goal, std::string name) :
    goal_(goal),
    name_(name),
    rows_(),
    columns_(),
    values_()
    {}

};  // class LPProblem

}  // namespace LPW

#endif  // LPW_LP_PROBLEM_HPP_
