#ifndef LPW_LP_PROBLEM_HPP_
#define LPW_LP_PROBLEM_HPP_

#include <memory>

#include "lpw/common.hpp"
#include "lpw/bounds.hpp"

namespace LPW {

class LPRow {
  size_t row_number_;
public:
  
};
typedef LPRowPtr std::shared_ptr<LPRow>;

class LPColumn {

};
typedef LPColumnPtr std::shared_ptr<LPColumn>;

class LPProblem {
public:
  static std::unique_ptr<LPProblem> CreateUnique();
  static std::shared_ptr<LPProblem> CreateShared();

  LPRowPtr CreateRow() = 0;

  LPColumnPtr CreateColumn() = 0;
};  // class LPProblem

}  // namespace LPW

#endif  // LPW_LP_PROBLEM_HPP_
