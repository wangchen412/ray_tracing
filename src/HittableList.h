#ifndef RT_HITTABLELIST_H
#define RT_HITTABLELIST_H

#include <memory>
#include <vector>

#include "Hittable.h"

using Hittable_ptr = std::shared_ptr<Hittable>;
using Hittable_ptrs = std::vector<Hittable_ptr>;

class HittableList : public Hittable {
  Hittable_ptrs objects_;

 public:
  HittableList() {}
  HittableList(Hittable_ptr object);

  void add(Hittable_ptr object);
  void clear();

  bool hit(const Ray& ray, const Interval& interval,
           HitRecord& rec) const override;
};

#endif