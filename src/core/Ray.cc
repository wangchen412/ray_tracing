#include "Ray.h"

Ray::Ray(const Point& origin, const Vector& direction)
    : origin_(origin), direction_(direction) {}

const Point& Ray::origin() const { return origin_; }
const Vector& Ray::direction() const { return direction_; }
Vector Ray::unit_direction() const { return direction_.normalized(); }
Point Ray::at(double t) const { return origin_ + direction_ * t; }