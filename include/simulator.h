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
    Simulator(const vec2& top_left_corner, size_t number_particles,
              size_t container_width, size_t container_height,
              size_t particle_mass, size_t particle_radius,
              const ci::Color& particle_color);

    /**
     * Updates the particles after one unit of time.
     */
    void Update();

    /**
     * Displays the current state of the particles in the Cinder application.
     */
    void Draw() const;

  private:
    vec2 top_left_corner_;

    vector<Particle> particles_;

    size_t container_width_;
    size_t container_height_;

    /**
     * Generates a random double between 0 and a given maximum value.
     *
     * @param max_value the max value to generate.
     *
     * @return a random double in the given range.
     */
    double GenerateRandomDouble(double max_value) const;
};

} // namespace visualizer

} // namespace idealgas