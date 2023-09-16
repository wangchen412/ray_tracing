#include "Interval.h"

#include "Math.h"

const Interval Interval::empty;
const Interval Interval::universe(-inf, inf);
const Interval Interval::unit(0, 0.999);

Interval::Interval() : min(inf), max(-inf) {}
Interval::Interval(double min, double max) : min(min), max(max) {}
bool Interval::contains(double x) const { return min <= x && x <= max; }
bool Interval::surrounds(double x) const { return min < x && x < max; }
void Interval::clamp(double& d) const {
  if (d < min) d = min;
  else if (d > max) d = max;
}
void Interval::clamp(Vector& v) const {
  clamp(v[0]);
  clamp(v[1]);
  clamp(v[2]);
}