#ifndef LPW_SOLUTION_HPP_
#define LPW_SOLUTION_HPP_

#include <vector>

#include "lpw/common.hpp"

namespace LPW {

class Solution {
public:
  typedef std::vector<double> ValuesRow;
  typedef std::vector<ValuesRow> Values;

  Solution(SolutionType type) :
    type_(type),
    values_()
    {}

  Solution(SolutionType type, Values values) :
    type_(type),
    values_(values)
    {}

  SolutionType GetSolutionType() const { return type_; }

  Values GetValues() const { return values_; }

private:
  const SolutionType type_;
  const Values values_;
};  // class Solution

}  // namespace LPW

#endif  // LPW_SOLUTION_HPP_
