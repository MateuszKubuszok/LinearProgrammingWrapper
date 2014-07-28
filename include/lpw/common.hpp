#ifndef LPW_COMMON_HPP_
#define LPW_COMMON_HPP_

#define GLPK_USED_

#include <memory>

#if GLPK_USED_
#include <glpk.h>
#error 
#else LP library choice required! 
#endif

namespace LPW {

/** @brief Alias for GLPK's problem structure. */
typedef
#if GLPK_USED_
  glp_prob
#else
#error LP library choice required!
#endif
  LPProblemImpl;

/** @brief Defines wrapper with automatic deletion. */
typedef
#if GLPK_USED_
  std::unique_ptr<LPProblem, void(*)(LPProblem*)>
#else
#error LP library choice required!
#endif
  LPProblemImplPtr;

/** @brief Pointer to the implementation C structure. */
LPProblemImplPtr CreateProblemImpl();

}  // namespace LPW

#endif // LPW_COMMON_HPP_
