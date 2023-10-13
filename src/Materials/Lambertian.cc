#include "Lambertian.h"

#include "HitRecord.h"
#include "Ray.h"

Lambertian::Lambertian(const Color& albedo) : albedo_(albedo) {}

bool Lambertian::scatter(const Ray& incident, const HitRecord& rec,
                         Color& atten, Ray& scattered) const {
  Vector dir = rec.normal + random_unit_vector<3>();
  if (near_zero(dir)) dir = rec.normal;
  scattered = Ray(rec.position, dir);
  atten = albedo_;
  return true;
}