#ifndef RT_MATH_H
#define RT_MATH_H

#include <Eigen/Dense>
#include <cmath>
#include <limits>
#include <random>

using Matrix = Eigen::MatrixXd;
using Vector = Eigen::Vector3d;
using Point = Vector;
using Color = Vector;

using std::abs;
using std::max;
using std::min;
using std::sqrt;

const double inf = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
const double epsilon = 1e-8;

inline double rad(double deg) { return deg * pi / 180; }
inline double deg(double rad) { return rad * 180 / pi; }

inline double random_double() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}
inline double random_double(double min, double max) {
  return min + random_double() * (max - min);
}

inline Vector random_unit_vector() {
  Vector v;
  do v.setRandom();
  while (v.squaredNorm() > 1);
  return v.normalized();
}

inline Vector random_on_hemisphere(const Vector& n) {
  auto v = random_unit_vector();
  return n.dot(v) > 0 ? v : -v;
}

inline Vector reflect(const Vector& v, const Vector& n) {
  return v - v.dot(n) * n * 2;
}

inline Vector refract(const Vector& v, const Vector& n, double index_ratio) {
  auto cos_theta = min(-v.dot(n), 1.0);
  auto r_x = index_ratio * (v + cos_theta * n);
  auto r_y = -sqrt(abs(1.0 - r_x.squaredNorm())) * n;
  return r_x + r_y;
}

inline bool near_zero(const Vector& v) {
  return v.x() < epsilon && v.y() < epsilon && v.z() < epsilon;
}

#endif