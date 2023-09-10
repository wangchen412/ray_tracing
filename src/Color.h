#ifndef RT_COLOR_H
#define RT_COLOR_H

#include <iostream>
#include <Eigen/Dense>

using Color = Eigen::Vector3d;

void write_color(std::ostream &os, const Color &color)
{
  os << static_cast<int>(255.999 * color[0]) << ' '
     << static_cast<int>(255.999 * color[1]) << ' '
     << static_cast<int>(255.999 * color[2]) << '\n';
}

#endif