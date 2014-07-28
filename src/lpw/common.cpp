#include "lpw/common.hpp"

#include <cstdlib>

namespace LPW {
#if GLPK_USED_

namespace {
void FreeGLPK() {
  glp_free_env();
}
}  // namespace

LPProblemImplPtr CreateProblemImpl() {
  static bool initialized = false;
  if (!initialized) {
    std::atexit(FreeGLPK);
    initialized = true;
  }

  return LPProblemImplPtr(glp_create_prob(), glp_delete_prob);
}

#else
#error LP library choice required!
#endif
}  // namespace LPW
