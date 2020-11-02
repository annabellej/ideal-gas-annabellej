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

    //maximum values of position/velocity for particles in container:
    size_t max_x_position_;
    size_t max_y_position_;
    int max_velocity_magnitude_;

    /**
     * Generates a random double between a given min and max value.
     *
     * @param max_value the max value to generate.
     * @param min_value the min value to generate.
     *
     * @return a random double in the given range.
     */
    double GenerateRandomDouble(double max_value, double min_value) const;

    /**
     * Handles a possible collision between a current particle and another.
     * Does nothing if particles do not collide (aka not touching or not moving
     * towards each other).
     * If particles do collide, velocity of current particle is adjusted
     * accordingly.
     *
     * @param current_particle the current particle to examine.
     * @param other_particle   the other particle to examine.
     */
    void HandlePossibleCollision(Particle& current_particle,
                                 const Particle& other_particle);
};

} // namespace visualizer

} // namespace idealgas