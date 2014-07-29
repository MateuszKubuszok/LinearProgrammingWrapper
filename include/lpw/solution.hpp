#ifndef LPW_SOLUTION_HPP_
#define LPW_SOLUTION_HPP_

#include <vector>

#include "lpw/common.hpp"

namespace LPW {

class Solution {
public:
  typedef std::vector<double> Values;

  Solution(SolutionType type) :
    type_(type),
    primal_values_(),
    dual_values_()
    {}

  Solution(SolutionType type, Values primal_values, Values dual_values) :
    type_(type),
    primal_values_(primal_values),
    dual_values_(dual_values)
    {}

  SolutionType GetSolutionType() const { return type_; }

  Values GetPrimalValues() const { return primal_values_; }

  Values GetDualValues() const { return dual_values_; }

private:
  const SolutionType type_;
  const Values primal_values_;
  const Values dual_values_;
};  // class Solution

}  // namespace LPW

#endif  // LPW_SOLUTION_HPP_
