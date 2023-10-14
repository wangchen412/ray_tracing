#include <fstream>
#include <iostream>

#include "Camera.h"
#include "Hittables.h"
#include "Materials.h"
#include "Ray.h"
#include "omp.h"

using std::make_shared;

int main() {
  omp_set_num_threads(4);
  srand((unsigned int)time(0));

  // Image
  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 1200;
  int image_height = std::max(int(image_width / aspect_ratio), 1);

  // Camera
  Camera camera(image_width, image_height);
  camera.set_position({13, 2, 3}, {0, 0, 0}, 20, 0.6, -3.5);
  camera.set_quality(50, 50);

  // Materials
  auto material0 = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
  auto material1 = make_shared<Dielectric>(1.5);
  auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
  auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5));

  // Objects
  HittableList world;
  world.add(make_shared<Sphere>(Point(0, -1000, 0), 1000, material0));
  world.add(make_shared<Sphere>(Point(0, 1, 0), 1, material1));
  world.add(make_shared<Sphere>(Point(-4, 1, 0), 1, material2));
  world.add(make_shared<Sphere>(Point(4, 1, 0), 1, material3));

  auto random_color = [](double min = 0, double max = 1) {
    return random_vector(min, max);
  };

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      Point center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if ((center - Point(4, 0.2, 0)).norm() > 0.9) {
        std::shared_ptr<Material> sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          Color albedo = random_color().cwiseProduct(random_color());
          sphere_material = make_shared<Lambertian>(albedo);
          world.add(make_shared<Sphere>(center, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = random_color(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphere_material = make_shared<Metal>(albedo, fuzz);
          world.add(make_shared<Sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = make_shared<Dielectric>(1.5);
          world.add(make_shared<Sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  // Render
  camera.render(world);

  return 0;
}