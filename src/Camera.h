#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "Hittable.h"
#include "Ray.h"

class Camera {
  Point center_{0, 0, 0};
  int image_width_, image_height_, samples_{10};
  double focal_{1}, height_{2}, width_;
  Vector u_, v_, du_, dv_;
  Point upper_left_, pixel_zero_;

  auto at(int i, int j) const;
  Ray ray(int i, int j) const;
  Ray ray_sample_square(int i, int j) const;
  Vector d_sample_square() const;
  static Color ray_color(const Ray& r, const Hittable& t);
  static void write_color(std::ostream& os, const Color& c, int n = 1);

 public:
  Camera(int image_width, int image_height);
  void render(const Hittable& objects) const;
};

#endif