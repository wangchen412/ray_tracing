#include <fstream>
#include <iostream>

#include "Camera.h"
#include "HittableList.h"
#include "Ray.h"
#include "Sphere.h"

int main() {
  // Image
  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = std::max(int(image_width / aspect_ratio), 1);

  // Camera
  Camera camera(image_width, image_height);

  // Objects
  HittableList objects(std::make_shared<Sphere>(Point(0, 0, -1), 0.5));
  objects.add(std::make_shared<Sphere>(Point(0, -100.5, -1), 100));

  // Render
  camera.render(objects);

  return 0;
}