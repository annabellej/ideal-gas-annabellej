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
    * Particle has no set mass, radius, or color.
    */
  Particle() : position(0,0), velocity(0,0) {};

  /**
    * Constructor for a Particle object given position and velocity.
    * Particle has no set mass, radius, or color.
    *
    * @param pos the initial (current) position of this Particle.
    * @param vel the initial (current) velocity of this Particle.
    */
  Particle(vec2 pos, vec2 vel) : position(pos), velocity(vel) {};

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
};

} // namespace idealgas