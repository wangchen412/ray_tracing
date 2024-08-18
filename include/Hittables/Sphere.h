#include <memory>

#include "Hittable.h"
#include "Math.h"

class Material;

class Sphere : public Hittable {
  Point center_;
  double radius_;
  std::shared_ptr<Material> material_;
  Vector center_vec_;
  bool is_moving_;

 public:
  Sphere(const Point& center, double radius,
         std::shared_ptr<Material> material);
  Sphere(const Point& center1, const Point& center2, double radius,
         std::shared_ptr<Material> material);
  bool hit(const Ray& ray, const Interval& interval,
           HitRecord& rec) const override;
  Vector normal(const Point& position) const;
  Point center(double time) const;
};