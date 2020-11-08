#include "core/particle_group.h"
#include "core/particle_utils.h"

namespace idealgas {

using idealgas::particleutils::GenerateRandomVelocity;
using idealgas::particleutils::GenerateRandomPosition;

ParticleGroup::ParticleGroup(size_t num_particles, size_t mass, size_t radius,
                             ci::Color color, double max_x_pos,
                             double max_y_pos, double max_velocity) {
  particle_mass_ = mass;
  particle_radius_ = radius;
  particle_color_ = color;

  max_x_position_ = max_x_pos;
  max_y_position_ = max_y_pos;
  max_velocity_magnitude_ = max_velocity;

  vec2 particle_velocity = GenerateRandomVelocity(max_velocity_magnitude_);

  for (int index = 0; index < num_particles; index++) {
    vec2 current_random_position = GenerateRandomPosition(max_x_pos, max_y_pos);
    particles_.push_back(Particle(current_random_position, particle_velocity,
                                  mass, radius, color));
  }
}

void ParticleGroup::Update() {
  //keep track of particles already updated if colliding with an earlier one
  vector<bool> updated_particles(particles_.size(), false);

  //loop through particles and update their positions
  for (int index = 0; index < particles_.size(); ++index) {
    //check if this particle already handled from collision with earlier one
    if (updated_particles.at(index)) {
      continue;
    }

    Particle& particle = particles_.at(index);

    //TODO: if(HandlePossibleWallCollision) -> continue;
    //TODO: if(HandlePossibleParticleCollision) -> add other particle to vector, continue;

    //check for collision w/ horizontal wall (top/bottom of container)
    if ((particle.position.y <= 0 && particle.velocity.y < 0) ||
        (particle.position.y >= max_y_position_ && particle.velocity.y > 0)) {
      particle.velocity.y = -particle.velocity.y;
    }
    //check for collision w/ vertical wall (left/right side of container)
    if ((particle.position.x <= 0 && particle.velocity.x < 0) ||
        (particle.position.x >= max_x_position_ && particle.velocity.x > 0)) {
      particle.velocity.x = -particle.velocity.x;
    }

    //check for collision w/ other particle
    for (int other_index = 0; other_index < particles_.size(); ++other_index) {
      Particle& other_particle = particles_.at(other_index);
      if (index != other_index) { //avoid comparing to itself
        if (HandlePossibleCollision(particle, other_particle)) {
          updated_particles.at(other_index) = true;
          continue;
        }
      }
    }

    //update particle's position
    particle.position += particle.velocity;
  }
}

size_t ParticleGroup::GetGroupSize() const {
  return particles_.size();
}

Particle ParticleGroup::GetParticleAt(size_t index) const {
  return particles_.at(index);
}

void ParticleGroup::ClearParticles() {
  particles_.clear();
}

void ParticleGroup::AddParticle(const Particle &particle) {
  particles_.push_back(particle);
}

bool ParticleGroup::HandlePossibleCollision(Particle &current_particle,
                                                Particle &other_particle) {
  double distance = length(current_particle.position - other_particle.position);
  bool are_moving_towards = //true if particles are moving towards each other
          dot(current_particle.velocity - other_particle.velocity,
              current_particle.position - other_particle.position) < 0;

  if ((distance <= current_particle.radius + other_particle.radius) &&
      are_moving_towards) {
    //store variables needed for calculations
    vec2 v1 = current_particle.velocity;
    vec2 v2 = other_particle.velocity;
    vec2 x1 = current_particle.position;
    vec2 x2 = other_particle.position;
    size_t m1 = current_particle.mass;
    size_t m2 = other_particle.mass;

    //calculate new velocity of first particle
    double multiplier1 = (2 * m2 / (m1 + m2)) *
                         (dot(v1 - v2, x1 - x2) / (length(x1 - x2) * length(x1 - x2)));
    current_particle.velocity = v1 - (vec2((x1 - x2).x * multiplier1,
                                           (x1 - x2).y * multiplier1));
    //calculate new velocity of second particle
    double multiplier2 = (2 * m1 / (m1 + m2)) *
                         (dot(v2 - v1, x2 - x1) / (length(x2 - x1) * length(x2 - x1)));
    other_particle.velocity = v2 - (vec2((x2 - x1).x * multiplier2,
                                         (x2 - x1).y * multiplier2));
    //update positions from new velocities
    current_particle.position += current_particle.velocity;
    other_particle.position += other_particle.velocity;
    return true;
  }

  return false;
}

} //namespace idealgas