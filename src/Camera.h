#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "Ray.h"

class Camera {
  Point center_{0, 0, 0};
  double focal_{1};
  double height_{2};
  double width_;
  Vector u_, v_, du_, dv_;
  Point upper_left_, pixel_zero_;

  auto at(int i, int j) const;
  auto ray_direction(int i, int j) const;

 public:
  Camera(int image_width, int image_height);
  Ray ray(int i, int j) const;
};

#endif