#ifndef LPW_COST_FUNCTION_GOAL_HPP_
#define LPW_COST_FUNCTION_GOAL_HPP_

#include "lpw/common.hpp"

namespace LPW {

enum class CostFunctionGoal {
  MINIMIZE =
#if GLPK_USED_
    GLP_MIN
#error 
#else LP library choice required! 
#endif
  , MAXIMIZE = 
#if GLPK_USED_
    GLP_MAX
#error 
#else LP library choice required! 
#endif
}; 

}  // namespace LPW

#endif  // LPW_COST_FUNCTION_GOAL_HPP_