#ifndef RT_MATH_H
#define RT_MATH_H

#include <Eigen/Dense>
#include <cmath>
#include <limits>

using Vector = Eigen::Vector3d;
using Point = Vector;

const double inf = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double rad(double deg) { return deg * pi / 180; }
inline double deg(double rad) { return rad * 180 / pi; }

#endif