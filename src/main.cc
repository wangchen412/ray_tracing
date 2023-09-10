#include <fstream>
#include <iostream>

#include "Camera.h"
#include "Color.h"
#include "Ray.h"

Color ray_color(const Ray& r) {
  auto a = 0.5 * (r.direction().normalized().y() + 1);
  return (1.0 - a) * Color{1, 1, 1} + a * Color(0.5, 0.7, 1);
}

int main() {
  // Image
  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = std::max(int(image_width / aspect_ratio), 1);

  // Camera
  Camera camera(image_width, image_height);

  // Render
  auto file = std::ofstream("image.ppm");
  file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = 0; j < image_height; ++j)
    for (int i = 0; i < image_width; ++i)
      write_color(file, ray_color(camera.ray(i, j)));

  std::clog << "Done!" << std::endl;
  file.close();

  return 0;
}