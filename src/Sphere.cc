#include "Sphere.h"

Sphere::Sphere(const Point& center, double radius, Material_ptr material)
    : center_(center), radius_(radius), material_(material) {}

bool Sphere::hit(const Ray& ray, const Interval& interval,
                 HitRecord& rec) const {
  auto d = ray.origin() - center_;
  auto a = ray.direction().squaredNorm();
  auto h = ray.direction().dot(d);
  auto c = d.squaredNorm() - radius_ * radius_;
  auto dis = h * h - a * c;

  if (dis < 0) return false;
  auto sqrt_dis = std::sqrt(dis);

  auto root = (-h - sqrt_dis) / a;
  if (!interval.surrounds(root)) {
    root = (-h + sqrt_dis) / a;
    if (!interval.surrounds(root)) return false;
  }

  rec.t = root;
  rec.position = ray.at(root);
  rec.set_face_normal(ray, *this);
  rec.material = material_;

  return true;
}

Vector Sphere::normal(const Point& position) const {
  return (position - center_) / radius_;
}
