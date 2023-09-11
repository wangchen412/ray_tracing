#include "Hittable.h"
#include "Ray.h"

class Sphere : public Hittable {
  Point center_;
  double radius_;

 public:
  Sphere(const Point& center, double radius);
  bool hit(const Ray& ray, double tmin, double tmax, HitRecord& rec) const;
  Vector normal(const Point& position) const;
};