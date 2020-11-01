#pragma once

#include <vector>
#include "particle.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

using std::vector;
using glm::vec2;

/**
 * A simulator that visualizes the motion of a number of ideal gas particles
 * inside a container over time.
 */
class Simulator {
  public:
    /**
     * Constructor for a Simulator.
     *
     * @param top_left_corner   the coordinates of container's top left corner.
     * @param number_particles  the number of particles in this simulation.
     * @param container_width   the width in pixels of the container.
     * @param container_height  the height in pixels of the container.
     */
    Simulator(const vec2& top_left_corner, size_t number_particles,
              size_t container_width, size_t container_height) :
              top_left_corner_(top_left_corner), particles_(number_particles),
              container_width_(container_width),
              container_height_(container_height) {};

    /**
     * Displays the current state of the particles in the Cinder application.
     */
    void Draw() const;

  private:
    vec2 top_left_corner_;
    vector<Particle> particles_;
    size_t container_width_;
    size_t container_height_;
};

} // namespace visualizer

} // namespace idealgas