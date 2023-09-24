#ifndef RT_HITTABLE_H
#define RT_HITTABLE_H

class Ray;
class Interval;
class HitRecord;

class Hittable {
 public:
  virtual bool hit(const Ray& ray, const Interval& interval,
                   HitRecord& rec) const = 0;
};

#endif