#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include "../Ray.h"

class HitRecord;

class Material {
 public:
  virtual bool scatter(const Ray& incident, const HitRecord& rec, Color& atten,
                       Ray& scattered) const = 0;
};

class Lambertian : public Material {
  Color albedo_;

 public:
  Lambertian(const Color& albedo);
  bool scatter(const Ray& incident, const HitRecord& rec, Color& atten,
               Ray& scattered) const override;
};

#endif