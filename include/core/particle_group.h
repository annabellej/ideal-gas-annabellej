#pragma once

#include <vector>
#include "particle.h"
#include "cinder/gl/gl.h"

namespace idealgas {

using std::vector;
using idealgas::Particle;

class ParticleGroup {
  public:
    /**
     * Constructor for a group of Particles.
     *
     * @param num_particles the number of particles in this group.
     *
     * @param mass          the mass of the particles in this group.
     * @param radius        the radius of the particles in this group.
     * @param color         the color of the particles in this group.
     *
     * @param max_x_pos     the maximum x position of particles.
     * @param max_y_pos     the maximum y position of particles.
     * @param max_velocity  the maximum velocity magnitude of particles.
     */
    ParticleGroup(size_t num_particles, size_t mass, size_t radius,
                  ci::Color color, double max_x_pos, double max_y_pos,
                  double max_velocity);

    /**
     * Updates all the positions of the particles in this group by one unit
     * of time.
     */
    void Update();

    /**
     * Fetches the size of this particle group, aka how many particles.
     *
     * @return  the number of particles in this group.
     */
    size_t GetGroupSize() const;

    /**
     * Fetch the particle at the given index in this IdealGasSimulator's vector of
     * particles.
     *
     * @param index the index of the particle to retrieve.
     *
     * @return a reference to the particle at the given index.
     */
    Particle GetParticleAt(size_t index) const;

    /**
     * Gets rid of all the particles in this IdealGasSimulator.
     */
    void ClearParticles();

    /**
     * Adds an additional particle to the IdealGasSimulator.
     *
     * @param particle the particle to add.
     */
    void AddParticle(const Particle& particle);

  private:
    vector<Particle> particles_;

    //particle details
    size_t particle_mass_;
    size_t particle_radius_;
    ci::Color particle_color_;

    //maximum values of position/velocity for particles in container:
    double max_x_position_;
    double max_y_position_;
    double max_velocity_magnitude_;

    /**
   * Handles a possible collision between a current particle and another.
   * Does nothing if particles do not collide (aka not touching or not moving
   * towards each other).
   * If particles do collide, velocity of current particle is adjusted
   * accordingly.
   *
   * @param current_particle the current particle to examine.
   * @param other_particle   the other particle to examine.
   *
   * @return true  if there was a collision between particles, else
   *         false if there was no collision.
   */
    bool HandlePossibleCollision(Particle& current_particle,
                                 Particle& other_particle);
};

} //namespace idealgas