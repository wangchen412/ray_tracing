#ifndef RT_DIELECTRIC_H
#define RT_DIELECTRIC_H

#include "Material.h"

class Dielectric : public Material {
  double ir_;

  static double reflectance(double cosine, double index_ratio);

 public:
  Dielectric(double refractive_index);
  bool scatter(const Ray& incident, const HitRecord& rec, Color& atten,
               Ray& scattered) const override;
};

#endif