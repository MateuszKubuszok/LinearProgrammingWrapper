#include "lpw/bounds.hpp"

namespace LPW {

namespace {

class Unbounded : public Bounds {
public:
  virtual BoundType GetType() const override {
  	return BoundType::Unbounded;
  }

  virtual double GetLowerBound() const override {
    return 0.0;
  }

  virtual double GetUpperBound() const override {
    return 0.0;
  }
};

class LowerBound : public Bounds {
  const double lower_bound_;
  
public:
  explicit LowerBound(double lower_bound) :
    lower_bound_(lower_bound)
    {}

  virtual BoundType GetType() const override {
  	return BoundType::LowerBound;
  }

  virtual double GetLowerBound() const override {
    return lower_bound_;
  }

  virtual double GetUpperBound() const override {
    return 0.0;
  }
};

class UpperBound : public Bounds {
  const double upper_bound_;

public:
  explicit UpperBound(double upper_bound) :
    upper_bound_(upper_bound)
    {}

  virtual BoundType GetType() const override {
  	return BoundType::UpperBound;
  }

  virtual double GetLowerBound() const override {
    return 0.0;
  }

  virtual double GetUpperBound() const override {
    return upper_bound_;
  }
};

class Range : public Bounds {
  const double lower_bound_;
  const double upper_bound_;

public:
  explicit Range(double lower_bound, double upper_bound) :
    lower_bound_(lower_bound),
    upper_bound_(upper_bound)
    {}

  virtual BoundType GetType() const override {
  	return BoundType::Range;
  }

  virtual double GetLowerBound() const override {
    return lower_bound_;
  }

  virtual double GetUpperBound() const override {
    return upper_bound_;
  }
};

class FixedPoint : public Bounds {
  const double fixed_point_;

public:
  explicit FixedPoint(double fixed_point) :
    fixed_point_(fixed_point)
    {}

  virtual BoundType GetType() const override {
  	return BoundType::FixedPoint;
  }

  virtual double GetLowerBound() const override {
    return fixed_point_;
  }

  virtual double GetUpperBound() const override {
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

}  // namespace LPW
