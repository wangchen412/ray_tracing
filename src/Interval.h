#ifndef RT_INTERVAL_H
#define RT_INTERVAL_H

#include "Math.h"

struct Interval {
  double min, max;

  Interval();
  Interval(double min, double max);
  bool contains(double x) const;
  bool surrounds(double x) const;
  void clamp(double& x) const;
  void clamp(Vector& v) const;

  static const Interval empty, universe, unit;
};

#endif