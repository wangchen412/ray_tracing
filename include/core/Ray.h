#ifndef RT_RAY_H
#define RT_RAY_H

#include "Math.h"

class Ray {
  Point origin_;
  Vector direction_;
  double time_;

 public:
  Ray() = default;
  Ray(const Point& origin, const Vector& direction, double time = 0);
  const Point& origin() const;
  const Vector& direction() const;
  Vector unit_direction() const;
  Point at(double t) const;
  double time() const;
};

#endif