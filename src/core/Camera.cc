#include "Camera.h"

#include <fstream>
#include <iostream>

#include "HitRecord.h"
#include "Hittable.h"
#include "Interval.h"
#include "Material.h"

Camera::Camera(int image_width, int image_height)
    : image_width_(image_width), image_height_(image_height) {}

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

  int remaining = image_height_;
#pragma omp parallel for shared(remaining)
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
    --remaining;
    if (omp_get_thread_num() == 0)
      std::clog << "\rScanlines remaining: " << remaining << ' ' << std::flush;
  }
  std::clog << "\rRendering done. Writing file..." << std::endl;
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

void Camera::set_position(const Vector& look_from, const Vector& look_at,
                          double vfov, const Vector& vup) {
  center_ = look_from;
  look_at_ = look_at;
  vfov_ = vfov;
  vup_ = vup;

  double focal_length = (center_ - look_at_).norm();
  height_ = 2 * tan(rad(vfov_ / 2)) * focal_length;
  width_ = height_ * image_width_ / image_height_;

  auto w = (center_ - look_at_) / focal_length;
  auto u = vup_.cross(w).normalized();
  auto v = w.cross(u);

  du_ = u * width_ / image_width_;
  dv_ = -v * height_ / image_height_;

  auto upper_left =
      center_ - u * width_ / 2 + v * height_ / 2 - w * focal_length;
  pixel_zero_ = upper_left + (du_ + dv_) / 2;
}

Point Camera::get_center() const { return center_; }