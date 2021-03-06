#ifndef LPW_BOUNDS_HPP_
#define LPW_BOUNDS_HPP_

#include <memory>

#include "lpw/common.hpp"

namespace LPW {

class Bounds;
typedef std::shared_ptr<Bounds> BoundsPtr;
class Bounds {
public:
  static BoundsPtr CreateUnbounded();
  static BoundsPtr CreateLowerBound(double lower_bound);
  static BoundsPtr CreateUpperBound(double upper_bound);
  static BoundsPtr CreateRange(double lower_bound, double upper_bound);
  static BoundsPtr CreateFixed(double fixed);

  virtual BoundType GetType() const = 0;
  virtual double GetLowerBound() const = 0;
  virtual double GetUpperBound() const = 0;
};  // class Bounds

}  // namespace LPW

#endif  // LPW_BOUNDS_HPP_
