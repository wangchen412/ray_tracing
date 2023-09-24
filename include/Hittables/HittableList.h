#ifndef RT_HITTABLELIST_H
#define RT_HITTABLELIST_H

#include <memory>
#include <vector>

#include "Hittable.h"

class HittableList : public Hittable {
  std::vector<std::shared_ptr<Hittable>> objects_;

 public:
  void add(std::shared_ptr<Hittable> object);
  void clear();

  bool hit(const Ray& ray, const Interval& interval,
           HitRecord& rec) const override;
};

#endif