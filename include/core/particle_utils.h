#pragma once

#include "cinder/gl/gl.h"
#include "core/particle.h"

namespace idealgas {

namespace particleutils {

using glm::vec2;
using idealgas::Particle;

/**
 * Generates a random double between a given min and max value.
 *
 * @param   max_value the max value to generate.
 * @param   min_value the min value to generate.
 *
 * @return  a random double in the given range.
 */
double GenerateRandomDouble(double max_value, double min_value);

/**
 * Generates a random velocity value under the given maximum value.
 *
 * @param max_magnitude the maximum value of the generated velocity.
 *
 * @return the generated random velocity value.
 */
vec2 GenerateRandomVelocity(double max_magnitude);

/**
 * Generates a random position value under the given max x and y values.
 *
 * @param max_x the maximum x value of the position.
 * @param max_y the maximum y value of the position.
 *
 * @return the generated random position value.
 */
vec2 GenerateRandomPosition(double max_x, double max_y);

/**
 * Velocity updated accordingly for particles colliding.
 *
 * @param first     the first particle to handle.
 * @param second    the second particle to handle.
 */
void HandleParticleCollision(Particle& first, const Particle& second);

/**
 * Checks if a collision between two particles happens.
 *
 * @param first     the first particle to check.
 * @param second    the second particle to check.
 *
 * @return  true    if a collision happens, else
 *          false   if a collision doesn't happen.
 */
bool ParticleCollisionExists(const Particle& first, const Particle& second);

} // namespace particleutils

} // namespace idealgas