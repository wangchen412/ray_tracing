#include "Sphere.h"

#include "HitRecord.h"
#include "Interval.h"
#include "Material.h"
#include "Ray.h"

Sphere::Sphere(const Point& center, double radius,
               std::shared_ptr<Material> material)
    : center_(center),
      radius_(radius),
      material_(material),
      is_moving_(false) {}

Sphere::Sphere(const Point& center1, const Point& center2, double radius,
               std::shared_ptr<Material> material)
    : center_(center1), radius_(radius), material_(material), is_moving_(true) {
  center_vec_ = center2 - center1;
}

bool Sphere::hit(const Ray& ray, const Interval& interval,
                 HitRecord& rec) const {
  auto d = ray.origin() - center(ray.time());
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

Point Sphere::center(double time) const {
  return is_moving_ ? center_ + center_vec_ * time : center_;
}