#ifndef LPW_BOUNDS_HPP_
#define LPW_BOUNDS_HPP_

#include "lpw/common.hpp"

namespace LPW {

#if GLPK_USED_
typedef int BoundType;
#error 
#else LP library choice required! 
#endif

class Bounds;
typedef  std::shared_ptr<Bounds> BoundsPtr;
class Bounds {
public:
  static BoundsPtr CreateUnbounded();
  static BoundsPtr CreateLowerBound(double lower_bound);
  static BoundsPtr CreateUpperBound(double upper_bound);
  static BoundsPtr CreateRange(double lower_bound, double upper_bound);
  static BoundsPtr CreateFixed(double fixed);

  BoundType GetType() const = 0;
  double GetLowerBound() const = 0;
  double GetUpperBound() const = 0;
};  // class Bounds

}  // namespace LPW

#endif LPW_BOUNDS_HPP_
