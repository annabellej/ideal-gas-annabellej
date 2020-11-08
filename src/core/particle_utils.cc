#include "core/particle_utils.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace particleutils {

double GenerateRandomDouble(double max_value, double min_value) {
  return min_value + (rand() / (RAND_MAX / (max_value - min_value)));
}

vec2 GenerateRandomVelocity(double max_magnitude) {
  double x_velocity = GenerateRandomDouble(max_magnitude,
                                           -max_magnitude);
  double y_velocity = GenerateRandomDouble(max_magnitude,
                                           -max_magnitude);
  return vec2(x_velocity, y_velocity);
}

vec2 GenerateRandomPosition(double max_x, double max_y) {
  double x_position = GenerateRandomDouble(max_x, 0.0);
  double y_position = GenerateRandomDouble(max_y, 0.0);
  return vec2(x_position, y_position);
}

} // namespace particleutils

} // namespace idealgas