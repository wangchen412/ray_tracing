#include "Ray.h"

class Sphere {
  Point center_;
  double radius_;

 public:
  Sphere(const Point& center, double radius);
  bool hit(const Ray& ray) const;
};