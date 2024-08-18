#ifndef RT_HITRECORD_H
#define RT_HITRECORD_H

#include <memory>

#include "Ray.h"

class Material;

struct HitRecord {
  double t;
  Point position;
  Vector normal;
  bool front_face;
  std::shared_ptr<Material> material;

  template <typename T>
  void set_face_normal(const Ray& ray, const T& hittable) {
    auto outward_normal = hittable.normal(position, ray.time());
    front_face = ray.direction().dot(outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

#endif