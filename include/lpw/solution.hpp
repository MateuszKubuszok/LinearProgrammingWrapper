#ifndef LPW_SOLUTION_HPP_
#define LPW_SOLUTION_HPP_

#include <vector>

#include "lpw/common.hpp"

namespace LPW {

class Solution {
  typedef std::vector<double> ValuesRow;
  typedef std::vector<ValuesRow> Values;

  const SolutionType type_;
  const Values values_;

public:
  Solution(SolutionType type) :
    type_(type),
    values_(),
    {}

  Solution(SolutionType type, Values values) :
    type_(type),
    values_(row_number),
    {}
};  // class Solution

}  // namespace LPW

#endif  // LPW_SOLUTION_HPP_