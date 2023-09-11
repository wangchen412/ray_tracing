#ifndef RT_HITTABLE_H
#define RT_HITTABLE_H

#include "Ray.h"

struct HitRecord {
  double t;
  Point position;
  Vector normal;
  bool front_face;

  template <typename T>
  void set_face_normal(const Ray& ray, const T& hittable) {
    auto outward_normal = hittable.normal(position);
    front_face = ray.direction().dot(outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class Hittable {
 public:
  virtual bool hit(const Ray& ray, double tmin, double tmax,
                   HitRecord& rec) const = 0;
};

#endif