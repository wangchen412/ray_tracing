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
  camera.set_position({-2, 2, 1}, {0, 0, -1}, 20, 10);

  // Material
  auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
  auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
  auto material_left = make_shared<Dielectric>(1.5);
  auto material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

  // Objects
  HittableList world;
  world.add(make_shared<Sphere>(Point(0, -100.5, -1), 100, material_ground));
  world.add(make_shared<Sphere>(Point(0, 0, -1), 0.5, material_center));
  world.add(make_shared<Sphere>(Point(-1, 0, -1), 0.5, material_left));
  world.add(make_shared<Sphere>(Point(-1, 0, -1), -0.4, material_left));
  world.add(make_shared<Sphere>(Point(1, 0, -1), 0.5, material_right));

  // Render
  camera.render(world);

  return 0;
}