#include "HittableList.h"

#include "HitRecord.h"
#include "Interval.h"
#include "Material.h"
#include "Ray.h"

void HittableList::add(std::shared_ptr<Hittable> object) {
  objects_.push_back(object);
}
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