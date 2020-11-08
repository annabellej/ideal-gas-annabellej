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

void HandleParticleCollision(Particle& first, const Particle& second) {
  vec2 v1 = first.velocity;
  vec2 v2 = second.velocity;
  vec2 x1 = first.position;
  vec2 x2 = second.position;
  size_t m1 = first.mass;
  size_t m2 = second.mass;

  //calculate new velocity of first particle
  double multiplier1 = (2.0 * m2 / (m1 + m2)) *
                       (dot(v1 - v2, x1 - x2) / (length(x1 - x2) * length(x1 - x2)));
  first.velocity = v1 - (vec2((x1 - x2).x * multiplier1,
                                         (x1 - x2).y * multiplier1));
}

bool ParticleCollisionExists(const Particle& first, const Particle& second) {
  double distance = length(first.position - second.position);
  bool are_moving_towards = dot(first.velocity - second.velocity,
                                first.position - second.position) < 0;

  return distance <= first.radius + second.radius && are_moving_towards;
}

} // namespace particleutils

} // namespace idealgas