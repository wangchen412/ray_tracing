#include "HittableList.h"

HittableList::HittableList(Hittable_ptr object) { add(object); }
void HittableList::add(Hittable_ptr object) { objects_.push_back(object); }
void HittableList::clear() { objects_.clear(); }
bool HittableList::hit(const Ray& ray, double tmin, double tmax,
                       HitRecord& rec) const {
  HitRecord tmp{.t = tmax};
  bool hit_anything = false;
  for (auto object : objects_) {
    if (object->hit(ray, tmin, tmp.t, tmp)) {
      hit_anything = true;
      rec = tmp;
    }
  }
  return hit_anything;
}