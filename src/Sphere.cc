#include "Sphere.h"

Sphere::Sphere(const Point& center, double radius)
    : center_(center), radius_(radius) {}

bool Sphere::hit(const Ray& ray) const {
  auto d = ray.origin() - center_;
  auto a = ray.direction().squaredNorm();
  auto b = ray.direction().dot(d) * 2;
  auto c = d.squaredNorm() - radius_ * radius_;
  return b * b - 4 * a * c >= 0;
}
