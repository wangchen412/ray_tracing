#include "Camera.h"

#include <fstream>
#include <iostream>

#include "HitRecord.h"
#include "Hittable.h"
#include "Interval.h"
#include "Material.h"

Camera::Camera(int image_width, int image_height)
    : image_width_(image_width), image_height_(image_height) {}

Point Camera::at(int i, int j) const {
  return film_ * Coord(i, j) + pixel_zero_;
}

Ray Camera::ray(int i, int j) const {
  Point source = center_;
  if (df_angle_ > 0) source += lens_ * random_unit_vector<2>();

  Point destination = at(i, j);
  if (samples_ > 1) destination += film_ * Coord::Random() * 0.5;

  return {source, destination - source};
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
#pragma omp parallel for shared(remaining) schedule(dynamic)
  for (int j = 0; j < image_height_; ++j) {
    for (int i = 0; i < image_width_; ++i) {
      Color c(0, 0, 0);
      for (int k = 0; k < samples_; ++k)
        c += ray_color(ray(i, j), max_depth_, objects);
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
  if (depth <= 0) return {0, 0, 0};

  HitRecord rec;
  if (t.hit(r, {0.001, inf}, rec)) {
    Ray scattered;
    Color attenuation;
    if (rec.material->scatter(r, rec, attenuation, scattered))
      return attenuation.cwiseProduct(ray_color(scattered, depth - 1, t));
    return {0, 0, 0};
  }

  auto a = 0.5 * (r.direction().normalized().y() + 1);
  return (1.0 - a) * Color{1, 1, 1} + a * Color(0.5, 0.7, 1);
}

void Camera::set_position(const Vector& look_from, const Vector& look_at,
                          double vfov, double df_angle, double focus_shift,
                          const Vector& vup) {
  center_ = look_from;
  look_at_ = look_at;
  vfov_ = vfov;
  df_angle_ = df_angle;
  vup_ = vup;

  double focal_dist = (center_ - look_at_).norm() + focus_shift;
  height_ = 2 * tan(rad(vfov_ / 2)) * focal_dist;
  width_ = height_ * image_width_ / image_height_;

  auto w = (center_ - look_at_).normalized();
  auto u = vup_.cross(w).normalized();
  auto v = w.cross(u);

  film_.col(0) = u * width_ / image_width_;
  film_.col(1) = -v * height_ / image_height_;

  auto defocus_radius = focal_dist * tan(rad(df_angle_ / 2));
  lens_.col(0) = u * defocus_radius;
  lens_.col(1) = v * defocus_radius;

  Point upper_left =
      center_ - u * width_ / 2 + v * height_ / 2 - w * focal_dist;
  pixel_zero_ = upper_left + film_ * Coord(0.5, 0.5);
}

Point Camera::get_center() const { return center_; }

void Camera::set_quality(int num_samples, int max_depth) {
  samples_ = num_samples;
  max_depth_ = max_depth;
}