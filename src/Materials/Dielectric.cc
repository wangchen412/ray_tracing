#include "Dielectric.h"

#include "HitRecord.h"

Dielectric::Dielectric(double refractive_index) : ir_(refractive_index) {}

bool Dielectric::scatter(const Ray& incident, const HitRecord& rec,
                         Color& atten, Ray& scattered) const {
  atten = Color(1, 1, 1);
  double refraction_ratio = rec.front_face ? (1 / ir_) : ir_;
  auto refracted =
      refract(incident.unit_direction(), rec.normal, refraction_ratio);
  scattered = Ray(rec.position, refracted);
  return true;
}