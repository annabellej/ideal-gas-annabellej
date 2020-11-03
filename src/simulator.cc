#include "simulator.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

using glm::vec2;
using glm::length;
using glm::dot;

Simulator::Simulator(const vec2 &top_left_corner, size_t number_particles,
                     size_t container_width, size_t container_height,
                     size_t particle_mass, size_t particle_radius,
                     const ci::Color& particle_color) {
  top_left_corner_ = top_left_corner;
  container_width_ = container_width;
  container_height_ = container_height;

  //generate given number of random particles
  max_x_position_ = (double) container_width_ - particle_radius * 2;
  max_y_position_ = (double) container_height_ - particle_radius * 2;
  max_velocity_magnitude_ = particle_radius * 0.5;

  //generate random velocity for all particles
  double x_velocity = GenerateRandomDouble(max_velocity_magnitude_,
                                           -max_velocity_magnitude_);
  double y_velocity = GenerateRandomDouble(max_velocity_magnitude_,
                                           -max_velocity_magnitude_);
  vec2 particle_velocity(x_velocity, y_velocity);

  for (int index = 0; index < number_particles; index++) {
    //generate random position
    double x_position = GenerateRandomDouble(max_x_position_, 0.0);
    double y_position = GenerateRandomDouble(max_y_position_, 0.0);
    vec2 particle_position(x_position, y_position);

    //add new particle to vector of particles
    particles_.push_back(Particle(particle_position, particle_velocity,
                               particle_mass, particle_radius, particle_color));
  }
}

void Simulator::Update() {
  //keep track of particles already updated if colliding with an earlier one
  vector<bool> updated_particles(particles_.size(), false);

  for (int index = 0; index < particles_.size(); ++index) {
    //check if this particle already handled from collision with earlier one
    if (updated_particles.at(index)) {
      continue;
    }

    Particle& particle = particles_.at(index);
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
      if (index != other_index) {
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

void Simulator::Draw() const {
  //draw rectangular container for particles
  vec2 pixel_bottom_right = top_left_corner_ +
                            vec2(container_width_, container_height_);
  ci::Rectf container_box(top_left_corner_, pixel_bottom_right);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(container_box);

  //draw particles inside container
  for (const Particle& particle: particles_) {
    size_t radius = particle.radius;
    vec2 screen_position = particle.position + top_left_corner_ +
                           vec2(radius, radius);
    ci::gl::color(ci::Color(particle.color));
    ci::gl::drawSolidCircle(screen_position, particle.radius);
  }
}

Particle& Simulator::GetParticleAt(size_t index) {
  return particles_.at(index);
}

void Simulator::ClearParticles() {
  particles_.clear();
}

void Simulator::AddParticle(const Particle &particle) {
  particles_.push_back(particle);
}

double Simulator::GenerateRandomDouble(double max_value, double min_value) const {
  return (max_value - min_value) * (double) rand() / (double) RAND_MAX;
}

bool Simulator::HandlePossibleCollision(Particle &current_particle,
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

} // namespace visualizer

} // namespace idealgas