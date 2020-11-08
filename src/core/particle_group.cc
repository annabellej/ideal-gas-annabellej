#include "core/particle_group.h"
#include "core/particle_utils.h"

namespace idealgas {

using idealgas::particleutils::GenerateRandomVelocity;
using idealgas::particleutils::GenerateRandomPosition;

ParticleGroup::ParticleGroup(size_t num_particles, size_t mass, size_t radius,
                             const ci::Color& color, double max_x_pos,
                             double max_y_pos, double max_velocity) {
  max_x_position_ = max_x_pos;
  max_y_position_ = max_y_pos;
  max_velocity_magnitude_ = max_velocity;

  particles_ = new vector<Particle>;
  vec2 particle_velocity = GenerateRandomVelocity(max_velocity_magnitude_);

  for (int index = 0; index < num_particles; index++) {
    vec2 current_random_position = GenerateRandomPosition(max_x_pos, max_y_pos);
    particles_->push_back(Particle(current_random_position, particle_velocity,
                                  mass, radius, color));
  }
}

ParticleGroup::~ParticleGroup() {
  delete[] particles_;
}

void ParticleGroup::HandlePossibleWallCollisions() {
  for (Particle& particle: *particles_) {
    //check for collision w/ horizontal wall (top/bottom side of container)
    if ((particle.position.y <= 0 && particle.velocity.y < 0) ||
        (particle.position.y >= max_y_position_ && particle.velocity.y > 0)) {
      particle.velocity.y = -particle.velocity.y;
    }
    //check for collision w/ vertical wall (left/right side of container)
    if ((particle.position.x <= 0 && particle.velocity.x < 0) ||
        (particle.position.x >= max_x_position_ && particle.velocity.x > 0)) {
      particle.velocity.x = -particle.velocity.x;
    }
  }
}

void ParticleGroup::UpdatePositions() {
  for (Particle& particle: *particles_) {
    particle.position += particle.velocity;
  }
}

size_t ParticleGroup::GetGroupSize() const {
  return particles_->size();
}

Particle* ParticleGroup::GetParticleAt(size_t index) const {
  return &particles_->at(index);
}

void ParticleGroup::ClearParticles() {
  particles_->clear();
}

void ParticleGroup::AddParticle(const Particle &particle) {
  particles_->push_back(particle);
}

} //namespace idealgas