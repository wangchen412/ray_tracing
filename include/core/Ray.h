#ifndef RT_RAY_H
#define RT_RAY_H

#include "Math.h"

class Ray {
  Point origin_;
  Vector direction_;

 public:
  Ray() = default;
  Ray(const Point& origin, const Vector& direction);
  const Point& origin() const;
  const Vector& direction() const;
  Vector unit_direction() const;
  Point at(double t) const;
  Vector reflection_simple_diffuse() const;
  Vector reflection_lambertian(const Vector& n) const;
};

#endif