#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "Ray.h"

class Hittable;

class Camera {
  Point center_, look_at_, pixel_zero_;
  int image_width_, image_height_, samples_{40}, max_depth_{20};
  double height_, width_, vfov_{90};
  Vector du_, dv_, vup_;

  auto at(int i, int j) const;
  Ray ray(int i, int j) const;
  Ray ray_sample_square(int i, int j) const;
  Vector d_sample_square() const;
  static Color ray_color(const Ray& r, int depth, const Hittable& t);
  void write_file(const Matrix& image) const;

 public:
  Camera(int image_width, int image_height);
  void render(const Hittable& objects) const;
  void set_position(const Vector& look_from, const Vector& look_at,
                    double vfov = 90, const Vector& vup = {0, 1, 0});
  Point get_center() const;
};

#endif