#include "Metal.h"

#include "HitRecord.h"

Metal::Metal(const Color& albedo, double fuzz)
    : albedo_(albedo), fuzz_(fuzz < 1 ? fuzz : 1) {}

bool Metal::scatter(const Ray& incident, const HitRecord& rec, Color& atten,
                    Ray& scattered) const {
  atten = albedo_;
  Vector dir = reflect(incident.direction().normalized(), rec.normal) +
               fuzz_ * random_unit_vector<3>();
  scattered = Ray(rec.position, dir);
  return dir.dot(rec.normal) > 0;
}