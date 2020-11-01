#pragma once

#include <vector>
#include "particle.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

using std::vector;

/**
 * A simulator that visualizes the motion of a number of ideal gas particles
 * inside a container over time.
 */
class Simulator {
  public:
    //TODO: write constructor comment after all vars needed are added, etc.
    Simulator(size_t number_particles) : particles_(number_particles) {};

    /**
     * Displays the current state of the particles in the Cinder application.
     */
    void Draw() const;

  private:
    vector<Particle> particles_;
};

} // namespace visualizer

} // namespace idealgas