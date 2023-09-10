#include "Sphere.h"

Sphere::Sphere(const Point& center, double radius)
    : center_(center), radius_(radius) {}

bool Sphere::hit(const Ray& ray, Point* position) const {
  auto d = ray.origin() - center_;
  auto a = ray.direction().squaredNorm();
  auto h = ray.direction().dot(d);
  auto c = d.squaredNorm() - radius_ * radius_;
  auto dis = h * h - a * c;
  bool real_root = dis >= 0;
  if (position && real_root) *position = ray.at((-h - std::sqrt(dis)) / a);
  return real_root;
}

Vector Sphere::normal(const Point& position) const {
  return (position - center_) / radius_;
}