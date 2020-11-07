#pragma once

#include <vector>
#include "particle.h"
#include "particle_utils.h"

namespace idealgas {

using std::vector;
using idealgas::Particle;

class ParticleGroup {
  public:
    //TODO: write header comment after all params added
    ParticleGroup(size_t num_particles) : particles_(num_particles) {};

  private:
    vector<Particle> particles_;
};

} //namespace idealgas