#include "Camera.h"

#include <fstream>
#include <iostream>

Camera::Camera(int image_width, int image_height)
    : image_width_(image_width), image_height_(image_height) {
  width_ = height_ * image_width / image_height;
  u_ = Vector(width_, 0, 0);
  v_ = Vector(0, -height_, 0);
  du_ = u_ / image_width;
  dv_ = v_ / image_height;
  upper_left_ = center_ - Vector(width_ / 2, -height_ / 2, focal_);
  pixel_zero_ = upper_left_ + (du_ + dv_) * 2;
}

auto Camera::at(int i, int j) const { return i * du_ + j * dv_ + pixel_zero_; }
Ray Camera::ray(int i, int j) const { return {center_, at(i, j) - center_}; }
Ray Camera::ray_sample_square(int i, int j) const {
  return {center_, at(i, j) + d_sample_square() - center_};
}

void Camera::write_color(std::ostream& os, const Color& c, int n) {
  Interval interval(0, 0.999);
  auto s = 1.0 / n;
  os << static_cast<int>(256 * interval.clamp(c[0] * s)) << ' '
     << static_cast<int>(256 * interval.clamp(c[1] * s)) << ' '
     << static_cast<int>(256 * interval.clamp(c[2] * s)) << '\n';
}

void Camera::render(const Hittable& objects) const {
  auto file = std::ofstream("image.ppm");
  file << "P3\n" << image_width_ << ' ' << image_height_ << "\n255\n";
  for (int j = 0; j < image_height_; ++j) {
    std::clog << "\rScanlines remaining: " << (image_height_ - j) << ' '
              << std::flush;
    for (int i = 0; i < image_width_; ++i) {
      Color c(0, 0, 0);
      for (int k = 0; k < samples_; ++k)
        c += ray_color(ray_sample_square(i, j), objects);
      write_color(file, c, samples_);
    }
  }
  std::clog << "\rDone!                    " << std::endl;
  file.close();
}

Color Camera::ray_color(const Ray& r, const Hittable& t) {
  HitRecord rec;
  if (t.hit(r, {0, inf}, rec))
    return 0.5 *
           ray_color({rec.position, random_on_hemisphere(r.direction())}, t);

  auto a = 0.5 * (r.direction().normalized().y() + 1);
  return (1.0 - a) * Color{1, 1, 1} + a * Color(0.5, 0.7, 1);
}

Vector Camera::d_sample_square() const {
  return du_ * (random_double() - 0.5) + dv_ * (random_double() - 0.5);
}