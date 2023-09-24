#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include "Math.h"

class Ray;
class HitRecord;

class Material {
 public:
  virtual bool scatter(const Ray& incident, const HitRecord& rec, Color& atten,
                       Ray& scattered) const = 0;
};

#endif