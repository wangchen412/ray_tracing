#include "Metal.h"
#include "../Hittable.h"

Metal::Metal(const Color& albedo) : albedo_(albedo) {}

bool Metal::scatter(const Ray& incident, const HitRecord& rec, Color& atten,
                    Ray& scattered) const {
  atten = albedo_;
  Vector dir = reflect(incident.direction(), rec.normal);
  scattered = Ray(rec.position, dir);
  return true;
}