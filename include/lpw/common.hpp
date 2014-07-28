#ifndef LPW_COMMON_HPP_
#define LPW_COMMON_HPP_

#ifdef GLPK_AVAILABLE
#ifndef LP_AVAILABLE_
#define LP_AVAILABLE_
#endif  // LP_AVAILABLE_
#endif  // GLPK_AVAILABLE

#ifndef LP_AVAILABLE_
#error LP library choice required! 
#endif 

namespace LPW {

enum class CostFunctionGoal {
  Minimize,
  Maximize
};

enum class BoundType {
  Unbounded,
  LowerBound,
  UpperBound,
  Range,
  FixedPoint
};

enum class VariableType {
  Continuous,
  Integer,
  Binary
};

enum class SolutionType {
  Optimal,
  Feasible,
  Infeasible,
  NoFeasible,
  Unbounded,
  Undefined
};

enum class ImplementationType {
#ifdef LP_AVAILABLE_
  GLPK,
#endif
  Default = 0
};

}  // namespace LPW

#endif  // LPW_COMMON_HPP_
