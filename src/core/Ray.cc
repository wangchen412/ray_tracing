#include "Ray.h"

Ray::Ray(const Point& origin, const Vector& direction, double time)
    : origin_(origin), direction_(direction), time_(time) {}

const Point& Ray::origin() const { return origin_; }
const Vector& Ray::direction() const { return direction_; }
Vector Ray::unit_direction() const { return direction_.normalized(); }
Point Ray::at(double t) const { return origin_ + direction_ * t; }
double Ray::time() const { return time_; }