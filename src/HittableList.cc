#include "HittableList.h"

HittableList::HittableList(Hittable_ptr object) { add(object); }
void HittableList::add(Hittable_ptr object) { objects_.push_back(object); }
void HittableList::clear() { objects_.clear(); }
bool HittableList::hit(const Ray& ray, const Interval& interval,
                       HitRecord& rec) const {
  HitRecord tmp{.t = interval.max};
  bool hit_anything = false;
  for (auto object : objects_) {
    if (object->hit(ray, {interval.min, tmp.t}, tmp)) {
      hit_anything = true;
      rec = tmp;
    }
  }
  return hit_anything;
}