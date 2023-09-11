#ifndef RT_RAY_H
#define RT_RAY_H

#include "Math.h"

class Ray {
  Point origin_;
  Vector direction_;

 public:
  Ray(const Point& origin, const Vector& direction);
  const Point& origin() const;
  const Vector& direction() const;
  Point at(double t) const;
};

#endif