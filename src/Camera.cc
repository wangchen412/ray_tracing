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
auto Camera::ray_direction(int i, int j) const { return at(i, j) - center_; }
Ray Camera::ray(int i, int j) const {
  return Ray(center_, ray_direction(i, j));
}

static void write_color(std::ostream& os, const Color& color) {
  os << static_cast<int>(255.999 * color[0]) << ' '
     << static_cast<int>(255.999 * color[1]) << ' '
     << static_cast<int>(255.999 * color[2]) << '\n';
}

void Camera::render(const Hittable& objects) const {
  auto file = std::ofstream("image.ppm");
  file << "P3\n" << image_width_ << ' ' << image_height_ << "\n255\n";
  for (int j = 0; j < image_height_; ++j) {
    std::clog << "\rScanlines remaining: " << (image_height_ - j) << ' '
              << std::flush;
    for (int i = 0; i < image_width_; ++i)
      write_color(file, ray_color(ray(i, j), objects));
  }
  std::clog << "\rDone!                    " << std::endl;
  file.close();
}

Color Camera::ray_color(const Ray& r, const Hittable& t) {
  HitRecord rec;
  if (t.hit(r, {0, inf}, rec)) return (rec.normal + Vector(1, 1, 1)) / 2;

  auto a = 0.5 * (r.direction().normalized().y() + 1);
  return (1.0 - a) * Color{1, 1, 1} + a * Color(0.5, 0.7, 1);
}