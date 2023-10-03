#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "Ray.h"

class Hittable;

class Camera {
  Point center_{0, 0, 0};
  int image_width_, image_height_, samples_{100}, max_depth_{50};
  double focal_{1}, height_, width_, vfov_{90};
  Vector u_, v_, du_, dv_;
  Point upper_left_, pixel_zero_;

  auto at(int i, int j) const;
  Ray ray(int i, int j) const;
  Ray ray_sample_square(int i, int j) const;
  Vector d_sample_square() const;
  static Color ray_color(const Ray& r, int depth, const Hittable& t);
  void write_file(const Matrix& image) const;

 public:
  Camera(int image_width, int image_height);
  void render(const Hittable& objects) const;
};

#endif