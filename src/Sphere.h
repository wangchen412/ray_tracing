#include "Hittable.h"
#include "Ray.h"

class Sphere : public Hittable {
  Point center_;
  double radius_;
  Material_ptr material_;

 public:
  Sphere(const Point& center, double radius, Material_ptr material);
  bool hit(const Ray& ray, const Interval& interval,
           HitRecord& rec) const override;
  Vector normal(const Point& position) const;
};