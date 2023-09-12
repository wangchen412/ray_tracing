#include "Interval.h"

#include "Math.h"

const Interval Interval::empty;
const Interval Interval::universe(-inf, inf);

Interval::Interval() : min(inf), max(-inf) {}
Interval::Interval(double min, double max) : min(min), max(max) {}
bool Interval::contains(double x) const { return min <= x && x <= max; }
bool Interval::surrounds(double x) const { return min < x && x < max; }
double Interval::clamp(double x) const {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}