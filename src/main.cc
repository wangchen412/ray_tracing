#include <fstream>
#include <iostream>

#include "Camera.h"
#include "Hittables.h"
#include "Materials.h"
#include "Ray.h"
#include "omp.h"

using std::make_shared;

int main() {
  omp_set_num_threads(8);

  // Image
  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = std::max(int(image_width / aspect_ratio), 1);

  // Camera
  Camera camera(image_width, image_height);

  // Material
  auto mat_1 = make_shared<Lambertian>(Color(0, 0, 1));
  auto mat_2 = make_shared<Lambertian>(Color(1, 0, 0));

  // Objects
  auto R = cos(pi / 4);
  HittableList objects;
  objects.add(make_shared<Sphere>(Point(-R, 0, -1), R, mat_1));
  objects.add(make_shared<Sphere>(Point(R, 0, -1), R, mat_2));

  // Render
  camera.render(objects);

  return 0;
}