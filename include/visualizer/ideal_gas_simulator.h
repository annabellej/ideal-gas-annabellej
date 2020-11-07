#pragma once

#include <vector>
#include "core/particle.h"
#include "core/particle_group.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

using std::vector;
using glm::vec2;

/**
 * A IdealGasSimulator that visualizes the motion of a number of ideal gas particles
 * inside a container over time.
 */
class IdealGasSimulator {
  public:
    /**
     * Constructor for a IdealGasSimulator.
     *
     * @param top_left_corner   the coordinates of container's top left corner.
     *
     * @param number_particles  the number of Particles in this simulation.
     *
     * @param container_width   the width in pixels of the container.
     * @param container_height  the height in pixels of the container.
     *
     * @param particle_mass     the mass of the Particles in this simulation.
     * @param particle_radius   the radius of the Particles in this simulation.
     * @param particle_color    the color of the Particles in this simulation.
     */
    IdealGasSimulator(const vec2& top_left_corner, size_t number_particles,
              size_t container_width, size_t container_height,
              size_t particle_mass, size_t particle_radius,
              const ci::Color& particle_color);

    /**
     * Updates the particles' movement after one unit of time.
     */
    void Update();

    /**
     * Displays the current state of the particles in the Cinder application.
     */
    void Draw() const;

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
    vec2 top_left_corner_;

    vector<Particle> particles_;

    size_t container_width_;
    size_t container_height_;

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

} // namespace visualizer

} // namespace idealgas