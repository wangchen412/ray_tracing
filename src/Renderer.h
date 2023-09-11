#include <fstream>

#include "Hittable.h"

Color ray_color(const Ray& r, const Hittable& t)
{
  HitRecord rec;
  if (t.hit(r, 0, 100, rec))
    return (rec.normal + Vector(1, 1, 1)) / 2;

  auto a = 0.5 * (r.direction().normalized().y() + 1);
  return (1.0 - a) * Color{1, 1, 1} + a * Color(0.5, 0.7, 1);
}

template <typename Func>
void render(Func f, int image_width, int image_height) {
  auto file = std::ofstream("image.ppm");
  file << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  for (int j = 0; j < image_height; ++j) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
              << std::flush;
    for (int i = 0; i < image_width; ++i) write_color(file, f(i, j));
  }
  std::clog << "\rDone!                    " << std::endl;
  file.close();
}