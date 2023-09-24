#include "Ray.h"

Ray::Ray(const Point& origin, const Vector& direction)
    : origin_(origin), direction_(direction) {}

const Point& Ray::origin() const { return origin_; }
const Vector& Ray::direction() const { return direction_; }
Point Ray::at(double t) const { return origin_ + direction_ * t; }
Vector Ray::reflection_simple_diffuse() const {
  return random_on_hemisphere(direction_);
}
Vector Ray::reflection_lambertian(const Vector& n) const {
  return n + random_unit_vector();
}