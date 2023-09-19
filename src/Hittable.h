#ifndef RT_HITTABLE_H
#define RT_HITTABLE_H

#include "Interval.h"
#include "Ray.h"
#include <memory>

class Material;
using Material_ptr = std::shared_ptr<Material>;

struct HitRecord {
  double t;
  Point position;
  Vector normal;
  bool front_face;
  Material_ptr material;

  template <typename T>
  void set_face_normal(const Ray& ray, const T& hittable) {
    auto outward_normal = hittable.normal(position);
    front_face = ray.direction().dot(outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class Hittable {
 public:
  virtual bool hit(const Ray& ray, const Interval& interval,
                   HitRecord& rec) const = 0;
};

#endif