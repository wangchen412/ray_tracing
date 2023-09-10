#include "Camera.h"

Camera::Camera(int image_width, int image_height) {
  width_ = height_ * image_width / image_height;
  u_ = Vector(width_, 0, 0);
  v_ = Vector(0, -height_, 0);
  du_ = u_ / image_width;
  dv_ = v_ / image_height;
  upper_left_ = center_ - Vector(width_ / 2, -height_ / 2, focal_);
  pixel_zero_ = upper_left_ + (du_ + dv_) * 2;
}

auto Camera::at(int i, int j) const { return i * du_ + j * dv_ + pixel_zero_; }
auto Camera::ray_direction(int i, int j) const { return at(i, j) - center_; }
Ray Camera::ray(int i, int j) const {
  return Ray(center_, ray_direction(i, j));
}
