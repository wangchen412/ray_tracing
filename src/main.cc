#include <fstream>
#include <iostream>

#include "Camera.h"
#include "Color.h"
#include "Ray.h"
#include "Renderer.h"

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
  render([&camera](auto i, auto j) { return ray_color(camera.ray(i, j)); },
         image_width, image_height);

  return 0;
}