#pragma once

#include <vector>
#include <map>
#include "core/particle.h"
#include "core/particle_group.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

using std::vector;
using std::map;
using glm::vec2;

/**
 * A IdealGasSimulator that visualizes the motion of a number of ideal gas particles
 * inside a container over time.
 */
class IdealGasSimulator {
  public:
    /**
     * Default constructor for an Ideal Gas Simulator.
     */
    IdealGasSimulator() = default;

    /**
     * Constructor for an Ideal Gas Simulator with multiple particle types.
     *
     * @param top_left_corner       coordinates of container's top left corner.
     *
     * @param particle_information  map w/ particle info + count
     *
     * @param container_width       the width in pixels of the container.
     * @param container_height      the height in pixels of the container.
     */
    IdealGasSimulator(const vec2& top_left_corner,
                      const map<Particle, size_t>& particle_information,
                      size_t container_width, size_t container_height);

    /**
     * Updates the particles' movement after one unit of time.
     */
    void Update();

    /**
     * Displays the current state of the particles in the Cinder application.
     */
    void Draw() const;

  private:
    vec2 top_left_corner_;
    size_t container_width_;
    size_t container_height_;

    vector<ParticleGroup*> particle_groups_;

    /**
     * Updates movements of all particles in all groups based on possible
     * collisions between any particles. Helper method for updating.
     */
    void HandleAllParticleCollisions();
};

} // namespace visualizer

} // namespace idealgas