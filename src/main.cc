#include <fstream>
#include <iostream>

#include "Camera.h"
#include "HittableList.h"
#include "Materials/Material.h"
#include "Materials/Metal.h"
#include "Ray.h"
#include "Sphere.h"
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
  auto mat_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
  auto mat_center = make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
  auto mat_left = make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
  auto mat_right = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

  // Objects
  HittableList objects;
  objects.add(make_shared<Sphere>(Point(0, -100.5, -1), 100, mat_ground));
  objects.add(make_shared<Sphere>(Point(0, 0, -1), 0.5, mat_center));
  objects.add(make_shared<Sphere>(Point(-1, 0, -1), 0.5, mat_left));
  objects.add(make_shared<Sphere>(Point(1, 0, -1), 0.5, mat_right));

  // Render
  camera.render(objects);

  return 0;
}