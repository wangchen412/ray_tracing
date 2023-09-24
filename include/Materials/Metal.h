#ifndef RT_METAL_H
#define RT_METAL_H

#include "Material.h"

class Metal : public Material {
  Color albedo_;
  double fuzz_;

 public:
  Metal(const Color& albedo, double fuzz = 0);
  bool scatter(const Ray& incident, const HitRecord& rec, Color& atten,
               Ray& scattered) const override;
};

#endif