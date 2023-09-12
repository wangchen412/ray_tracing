#ifndef RT_INTERVAL_H
#define RT_INTERVAL_H

struct Interval {
  double min, max;

  Interval();
  Interval(double min, double max);
  bool contains(double x) const;
  bool surrounds(double x) const;
  double clamp(double x) const;

  static const Interval empty, universe;
};

#endif