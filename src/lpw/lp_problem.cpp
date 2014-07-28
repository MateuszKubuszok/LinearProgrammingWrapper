#include "lpw/lp_problem.hpp"

#include "lpw/glp_problem.hpp"

namespace LPW {

namespace {

LPProblem* CreateRaw(
    ImplementationType impl,
    CostFunctionGoal goal,
    std::string name) {
  switch(impl) {
  
#ifdef GLPK_AVAILABLE
  case ImplementationType::GLPK:
    return new GlpProblem(goal, name);
#endif  // GLPK_AVAILABLE

  default:
    // assert(false);
    return nullptr;
  }
}

}  // namespace

std::unique_ptr<LPProblem> LPProblem::CreateUnique(
    ImplementationType impl,
    CostFunctionGoal goal,
    std::string name) {
  return std::unique_ptr<LPProblem>(CreateRaw(impl, goal, name));
}

std::shared_ptr<LPProblem> LPProblem::CreateShared(
    ImplementationType impl,
    CostFunctionGoal goal,
    std::string name) {
  return std::shared_ptr<LPProblem>(CreateRaw(impl, goal, name));
}

RowPtr LPProblem::CreateRow(BoundsPtr bounds, std::string name) {
  RowPtr row = std::shared_ptr<Row>(new Row(rows_.size(), bounds, name));
  rows_.push_back( row );
  return row;
}

ColumnPtr LPProblem::CreateColumn(BoundsPtr bounds, double coefficient, std::string name) {
  ColumnPtr column = std::shared_ptr<Column>(new Column(columns_.size(), bounds, coefficient, name));
  columns_.push_back( column );
  return column;
}

ValuePtr LPProblem::AddValue(RowPtr row, ColumnPtr column, double inner_value) {
  ValuePtr value = std::shared_ptr<Value>(new Value(row, column, inner_value));
  values_.push_back( value );
  return value;
}

} // namespace LPW
