#ifdef GLPK_AVAILABLE

#include <cstdlib>

#include "lpw/glp_problem.hpp"

namespace LPW {

namespace {

int Map0IndexedTo1Indexed(int value) {
  return value + 1;
}

int Map1IndexedTo0Indexed(int value) {
  return value - 1;
}

int Map(CostFunctionGoal goal) {
  switch(goal) {
  case CostFunctionGoal::Minimize:
    return GLP_MIN;
  case CostFunctionGoal::Maximize:
    return GLP_MAX;
  default:
    // assert(false);
    return 0;
  }
}

int Map(BoundType type) {
  switch(type) {
  case BoundType::Unbounded:
    return GLP_FR;
  case BoundType::LowerBound:
    return GLP_LO;
  case BoundType::UpperBound:
    return GLP_UP;
  case BoundType::Range:
    return GLP_DB;
  case BoundType::FixedPoint:
    return GLP_FX;
  default:
    // assert(false);
    return 0;
  }
}

int Map(VariableType type) {
  switch(type) {
  case VariableType::Continuous:
    return GLP_CV;
  case VariableType::Integer:
    return GLP_IV;
  case VariableType::Binary:
    return GLP_BV;
  default:
    // assert(false);
    return 0;
  }
}

SolutionType MapSolutionType(int type) {
  switch(type) {
  case GLP_OPT:
    return SolutionType::Optimal;
  case GLP_FEAS:
    return SolutionType::Feasible;
  case GLP_INFEAS:
    return SolutionType::Infeasible;
  case GLP_NOFEAS:
    return SolutionType::NoFeasible;
  case GLP_UNBND:
    return SolutionType::Unbounded;
  case GLP_UNDEF:
    return SolutionType::Undefined;
  default:
    // assert(false);
    return SolutionType::Undefined;
  }
}

void FreeGLPK() {
  glp_free_env();
}

GlpProblem::glp_prob_ptr CreateProblem() {
  bool glpk_initialized = false;
  if (!glpk_initialized) {
    std::atexit(FreeGLPK);
    glpk_initialized = true;
  }
  return GlpProblem::glp_prob_ptr(glp_create_prob(), glp_delete_prob);
}

void SetupProblem(
    glp_prob* problem,
    const CostFunctionGoal& goal,
    const std::string& name,
    const std::vector<RowPtr> rows,
    const std::vector<ColumnPtr> columns) {
  glp_set_prob_name(problem, name.c_str());
  glp_set_obj_dir(problem, Map(goal));

  glp_add_cols(problem, columns.size());
  for (const ColumnPtr& colPtr : columns) {
    const int column         = Map0IndexedTo1Indexed(colPtr->GetColumnNumber());
    const BoundsPtr bounds   = colPtr->GetBounds();
    const double coefficient = colPtr->GetCoefficient();
    const std::string name   = colPtr->GetName();

    glp_set_col_bnds(problem, column, Map(bounds->GetType()),
                                      bounds->GetLowerBound(),
                                      bounds->GetUpperBound());
    glp_set_obj_coef(problem, column, coefficient);
    glp_set_col_kind(problem, column, Map(colPtr->GetType()));
    glp_set_col_name(problem, column, name.c_str());
  }

  glp_add_rows(problem, rows.size());
  for (const RowPtr& rowPtr : rows) {
    const int row            = Map0IndexedTo1Indexed(rowPtr->GetRowNumber());
    const BoundsPtr bounds   = rowPtr->GetBounds();
    const std::string name   = rowPtr->GetName();

    glp_set_row_bnds(problem, row, Map(bounds->GetType()),
                                      bounds->GetLowerBound(),
                                      bounds->GetUpperBound());
    glp_set_row_name(problem, row, name.c_str());
  }
}
 
void FillProblem(glp_prob* problem, const std::vector<ValuePtr> values) {
  std::vector<int>    raw_rows;
  std::vector<int>    raw_columns;
  std::vector<double> raw_values;

  raw_rows.reserve(Map0IndexedTo1Indexed(values.size()));
  raw_rows.push_back(0);
  raw_columns.reserve(Map0IndexedTo1Indexed(values.size()));
  raw_columns.push_back(0);
  raw_values.reserve(Map0IndexedTo1Indexed(values.size()));
  raw_values.push_back(0);

  for (const ValuePtr& valuePtr : values) {
    raw_rows.push_back(
        Map0IndexedTo1Indexed(valuePtr->GetRow()->GetRowNumber()));
    raw_columns.push_back(
        Map0IndexedTo1Indexed(valuePtr->GetColumn()->GetColumnNumber()));
    raw_values.push_back(valuePtr->GetValue());
  }

  glp_load_matrix(problem, values.size(),
      &raw_rows[0], &raw_columns[0], &raw_values[0]);
}

Solution SolveProblem(glp_prob* problem, 
                      const std::vector<RowPtr> rows,
                      const std::vector<ColumnPtr> columns) {
  glp_smcp parm;
  glp_init_smcp(&parm);
  parm.msg_lev = GLP_MSG_OFF;

  bool success          = (glp_simplex(problem, &parm) != 0);
  SolutionType solution = MapSolutionType(glp_get_prim_stat(problem));
  if (!success ||
       (solution != SolutionType::Optimal &&
        solution != SolutionType::Feasible)) {
    return solution;
  }

  Solution::Values primal_values;
  primal_values.reserve(columns.size());
  for (const ColumnPtr& column : columns) {
    // assert that column numbers matches
    primal_values.push_back(
      glp_get_col_prim(problem, 
                       Map0IndexedTo1Indexed(column->GetColumnNumber())));
  }

  Solution::Values dual_values;
  dual_values.reserve(rows.size());
  for (const RowPtr& row : rows) {
    // assert that row numbers matches
    dual_values.push_back(
      glp_get_col_dual(problem, 
                       Map0IndexedTo1Indexed(row->GetRowNumber())));
  }

  return Solution(solution, primal_values, dual_values);
}

}  // namespace

Solution GlpProblem::Solve() const {
  glp_prob_ptr problem_ptr = CreateProblem();
  SetupProblem(problem_ptr.get(), goal_, name_, rows_, columns_);
  FillProblem(problem_ptr.get(), values_);
  return SolveProblem(problem_ptr.get(), rows_, columns_);
}

}  // namespace LPW

#endif  // GLPK_AVAILABLE
