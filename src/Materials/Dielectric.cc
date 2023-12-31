#include "Dielectric.h"

#include "HitRecord.h"

Dielectric::Dielectric(double refractive_index) : ir_(refractive_index) {}

bool Dielectric::scatter(const Ray& incident, const HitRecord& rec,
                         Color& atten, Ray& scattered) const {
  atten = Color(1, 1, 1);
  double refraction_ratio = rec.front_face ? (1 / ir_) : ir_;

  auto unit_direction = incident.unit_direction();
  auto c = min(-unit_direction.dot(rec.normal), 1.0);
  auto s = sqrt(1 - c * c);
  auto direction = refraction_ratio * s > 1.0 ||
                           reflectance(c, refraction_ratio) > random_double()
                       ? reflect(unit_direction, rec.normal)
                       : refract(unit_direction, rec.normal, refraction_ratio);
  scattered = Ray(rec.position, direction);
  return true;
}

double Dielectric::reflectance(double cosine, double r) {
  auto r0 = (1 - r) / (1 + r);
  r0 *= r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}