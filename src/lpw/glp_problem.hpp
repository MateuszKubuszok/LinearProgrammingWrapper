#ifndef LPW_GLP_PROBLEM_
#define LPW_GLP_PROBLEM_
#ifdef  GLPK_AVAILABLE

#include <memory>
#include <glpk.h>

#include "lpw/lp_problem.hpp"

namespace LPW {

class GlpProblem : public LPProblem {
public:
  typedef std::unique_ptr<glp_prob, void(*)(glp_prob*)> glp_prob_ptr;
  
  GlpProblem(CostFunctionGoal goal, std::string name) :
    LPProblem(goal, name)
    {}

  virtual Solution Solve() const override;
};

}  // namespace LPW

#endif  // GLPK_AVAILABLE
#endif  // LPW_GLP_PROBLEM_
