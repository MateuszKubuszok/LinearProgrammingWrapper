#include "lpw/glp_problem.hpp"
#ifdef  GLPK_AVAILABLE

#include <cstdlib>
#include <glpk.h>

namespace LPW {

namespace {

void FreeGLPK() {
  glp_free_env();
}

glp_prob_ptr CreateProblem() {
  bool glpk_initialized = false;
  if (!glpk_initialized) {
    std::atexit(FreeGLPK);
    glpk_initialized = true;
  }
  return glp_prob_ptr(glp_create_prob(), glp_delete_prob);
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
    return GLP_FP;
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

int Map(SolutionType type) {
  switch(type) {
  case Solution::Optimal:
    return GLP_OPT;
  case Solution::Feasible:
    return GLP_FEAS;
  case Solution::Infeasible:
    return GLP_INFEAS;
  case Solution::NoFeasible:
    return GLP_NOFEAS;
  case Solution::Unbounded:
    return GLP_UNBND;
  case Solution::Undefined:
    return GLP_UNDEF;
  default:
    // assert(false);
    return 0;
  }
}

}  // namespace

Solution GlpProblem::Solve() const {
  // TODO
  return SolutionType::Undefined;
}

}  // namespace LPW

#endif  // GLPK_AVAILABLE