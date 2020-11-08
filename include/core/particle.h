#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

using glm::vec2;
using ci::Color;

/**
 * Represents an ideal gas particle.
 */
struct Particle {
  vec2 position;
  vec2 velocity;
  size_t mass;
  size_t radius;
  Color color;

  /**
    * Default constructor for a Particle object.
    * Particle is at origin with no velocity.
    * Default mass = 1, radius = 1, color is white.
    */
  Particle() : position(0,0), velocity(0,0), mass(1), radius(1),
               color("white") {};

  /**
    * Constructor for a Particle object given all fields.
    *
    * @param pos the initial (current) position of this Particle.
    * @param vel the initial (current) velocity of this Particle.
    * @param m   the mass of this Particle.
    * @param r   the radius of this Particle.
    * @param c   the color of this Particle.
    */
  Particle(vec2 pos, vec2 vel, size_t m, size_t r, Color c) : position(pos),
                                                              velocity(vel),
                                                              mass(m),
                                                              radius(r),
                                                              color(c) {};

  /**
     * Operator overload for < operator. Necessary for Particle use in map.
     *
     * @param lhs the left hand side group to compare.
     * @param rhs the right hand side group to compare.
     *
     * @return true if left side has smaller mass then radius than right side,
     *         false if left side doesn't have smaller mass/radius.
     */
  friend bool operator<(const Particle& lhs, const Particle& rhs);
};

} // namespace idealgas