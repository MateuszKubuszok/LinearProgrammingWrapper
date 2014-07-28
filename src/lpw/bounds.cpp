#include "lpw/bounds.hpp"

namespace LPW {

#if GLPK_USED_

namespace {

class Unbounded : Bounds {
public:
  BoundType GetType() const override {
  	return GLP_FR;
  }

  double GetLowerBound() const override {
    return 0.0;
  }

  double GetUpperBound() const override {
    return 0.0;
  }
};

class LowerBound : Bounds {
  double lower_bound_;
  
public:
  explicit LowerBound(double lower_bound) :
    lower_bound_(lower_bound)
    {}

  BoundType GetType() const override {
  	return GLP_LO;
  }

  double GetLowerBound() const override {
    return lower_bound_;
  }

  double GetUpperBound() const override {
    return 0.0;
  }
};

class UpperBound : Bounds {
  double upper_bound_;

public:
  explicit UpperBound(double upper_bound) :
    upper_bound_(upper_bound)
    {}

  BoundType GetType() const override {
  	return GLP_UP;
  }

  double GetLowerBound() const override {
    return 0.0;
  }

  double GetUpperBound() const override {
    return upper_bound_;
  }
};

class Range : Bounds {
  double lower_bound_;
  double upper_bound_;

public:
  explicit Range(double lower_bound, double upper_bound) :
    lower_bound_(lower_bound),
    upper_bound_(upper_bound)
    {}

  BoundType GetType() const override {
  	return GLP_DB;
  }

  double GetLowerBound() const override {
    return lower_bound_;
  }

  double GetUpperBound() const override {
    return upper_bound_;
  }
};

class FixedPoint : Bounds {
  double fixed_point_;

public:
  explicit FixedPoint(double fixed_point) :
    fixed_point_(fixed_point)
    {}

  BoundType GetType() const override {
  	return GLP_FX;
  }

  double GetLowerBound() const override {
    return fixed_point_;
  }

  double GetUpperBound() const override {
    return fixed_point_;
  }
};

}  // namespace

BoundsPtr Bounds::CreateUnbounded() {
  return std::make_shared<Unbounded>();
}

BoundsPtr Bounds::CreateLowerBound(double lower_bound) {
  return std::make_shared<LowerBound>(lower_bound);
}

BoundsPtr Bounds::CreateUpperBound(double upper_bound) {
  return std::make_shared<UpperBound>(upper_bound);
}

BoundsPtr Bounds::CreateRange(double lower_bound, double upper_bound) {
  return std::make_shared<Range>(lower_bound, upper_bound);
}

BoundsPtr Bounds::CreateFixed(double fixed_point) {
  return std::make_shared<FixedPoint>(fixed_point);
}

#error 
#else LP library choice required! 
#endif

}  // namespace LPW
