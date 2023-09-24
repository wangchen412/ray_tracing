#ifndef RT_LAMBERTIAN_H
#define RT_LAMBERTIAN_H

#include "Material.h"

class HitRecord;

class Lambertian : public Material {
  Color albedo_;

 public:
  Lambertian(const Color& albedo);
  bool scatter(const Ray& incident, const HitRecord& rec, Color& atten,
               Ray& scattered) const override;
};

#endif