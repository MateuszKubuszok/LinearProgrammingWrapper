#include "lpw/lp_problem.hpp"

#include "lpw/glp_problem.hpp"

namespace LPW {

namespace {

LPProblem* CreateRaw(
    ImplementationType impl,
    CostFunctionGoal goal,
    std::string name) {
  switch(impl):
  
  #ifdef GLPK_AVAILABLE
  case ImplementationType::GLPK:
    return new GlpProblem(goal, name);
  #endif  // GLPK_AVAILABLE

  default:
    // assert(false);
    return nullptr;
}

}  // namespace

static std::unique_ptr<LPProblem> CreateUnique(
    ImplementationType impl,
    CostFunctionGoal goal,
    std::string name) {
  return std::unique_ptr<LPProblem>(CreateRaw(impl, goal, name));
}

static std::shared_ptr<LPProblem> CreateShared(
    ImplementationType impl,
    CostFunctionGoal goal
    std::string name) {
  return std::shared_ptr<LPProblem>(CreateRaw(impl, goal, name));
}

RowPtr LPProblem::CreateRow(BoundsPtr bounds, std::string name) {
  RowPtr row = std::make_shared<Row>(rows_.size(), bounds, name);
  rows_.push_back( row );
  return row;
}

ColumnPtr LPProblem::CreateColumn(BoundsPtr bounds, double coefficient, std::string name) {
  ColumnPtr column = std::make_shared<Column>(columns_.size(), bounds, coefficient, name);
  columns_.push_back( column );
  return column;
}

ValuePtr LPProblem::AddValue(RowPtr row, ColumnPtr column, double value) {
  ValuePtr value = std::make_shared<Value>(row, column, value);
  values_.push_back( value );
  return value;
}

} // namespace LPW
