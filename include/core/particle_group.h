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
                  const ci::Color& color, double max_x_pos, double max_y_pos,
                  double max_velocity);

    /**
     * Destructor for a Particle Group.
     */
    ~ParticleGroup();

    /**
     * Updates velocities of any particles colliding with walls.
     */
    void HandlePossibleWallCollisions();

    /**
     * Updates all positions of particles according to velocities.
     */
    void UpdatePositions();

    /**
     * Fetches the size of this particle group, aka how many particles.
     *
     * @return  the number of particles in this group.
     */
    size_t GetGroupSize() const;

    /**
     * Fetch a pointer to the particle at the given index in this
     * IdealGasSimulator's vector of particles.
     *
     * @param index the index of the particle to retrieve.
     *
     * @return a pointer to the particle at the given index.
     */
    Particle* GetParticleAt(size_t index) const;

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
    vector<Particle>* particles_;

    //maximum values of position/velocity for particles in container:
    double max_x_position_;
    double max_y_position_;
    double max_velocity_magnitude_;
};

} //namespace idealgas