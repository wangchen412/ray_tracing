#include "Camera.h"

#include <fstream>
#include <iostream>

#include "Materials/Material.h"

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

void Camera::write_file(const Matrix& image) const {
  auto file = std::ofstream("image.ppm");
  file << "P3\n" << image_width_ << ' ' << image_height_ << "\n255\n";
  for (int i = 0; i < image.cols(); ++i)
    file << static_cast<int>(256 * image(0, i)) << ' '
         << static_cast<int>(256 * image(1, i)) << ' '
         << static_cast<int>(256 * image(2, i)) << '\n';
  file.close();
}

void Camera::render(const Hittable& objects) const {
  Matrix image(3, image_height_ * image_width_);
  std::clog << "Rendering..." << std::endl;
#pragma omp parallel for
  for (int j = 0; j < image_height_; ++j) {
    for (int i = 0; i < image_width_; ++i) {
      Color c(0, 0, 0);
      for (int k = 0; k < samples_; ++k)
        c += ray_color(ray_sample_square(i, j), max_depth_, objects);
      c /= samples_;
      c = c.cwiseSqrt();
      Interval::unit.clamp(c);
      image.col(j * image_width_ + i) = c;
    }
  }
  std::clog << "Rendering done. Writing file..." << std::endl;
  write_file(image);
  std::clog << "All done!" << std::endl;
}

Color Camera::ray_color(const Ray& r, int depth, const Hittable& t) {
  if (depth <= 0) return {};

  HitRecord rec;
  if (t.hit(r, {0.001, inf}, rec)) {
    Ray scattered;
    Color attenuation;
    if (rec.material->scatter(r, rec, attenuation, scattered))
      return attenuation.cwiseProduct(ray_color(scattered, depth - 1, t));
    return {};
  }

  auto a = 0.5 * (r.direction().normalized().y() + 1);
  return (1.0 - a) * Color{1, 1, 1} + a * Color(0.5, 0.7, 1);
}

Vector Camera::d_sample_square() const {
  return du_ * (random_double() - 0.5) + dv_ * (random_double() - 0.5);
}