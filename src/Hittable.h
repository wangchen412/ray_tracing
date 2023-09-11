#ifndef RT_HITTABLE_H
#define RT_HITTABLE_H

#include "Ray.h"

struct HitRecord {
  Point position;
  Vector normal;
  double t;
};

class Hittable {
 public:
  virtual bool hit(const Ray& ray, double tmin, double tmax,
                   HitRecord& rec) const = 0;
};

#endif