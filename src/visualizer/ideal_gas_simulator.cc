#include "visualizer/ideal_gas_simulator.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

using glm::vec2;
using glm::length;
using glm::dot;

IdealGasSimulator::IdealGasSimulator(const vec2 &top_left_corner,
                                     const map<Particle, size_t> &particle_information,
                                     size_t container_width,
                                     size_t container_height) {
  top_left_corner_ = top_left_corner;
  container_width_ = container_width;
  container_height_ = container_height;

  for (auto const& entry: particle_information) {
    size_t num_particles = entry.second;
    size_t mass = entry.first.mass;
    size_t radius = entry.first.radius;
    ci::Color color = entry.first.color;

    double max_x_position = (double) container_width - radius * 2;
    double max_y_position = (double) container_height - radius * 2;
    double max_velocity = radius * 0.5; //v is small relative to r

    particle_groups_.push_back(ParticleGroup(num_particles, mass, radius, color,
                                             max_x_position, max_y_position,
                                             max_velocity));
  }
}

void IdealGasSimulator::Update() {
  //for each particle group in simulator, update particles
  for (ParticleGroup& group: particle_groups_) {
    group.Update();
  }
}

void IdealGasSimulator::Draw() const {
  //draw rectangular container for particles
  vec2 pixel_bottom_right = top_left_corner_ +
                            vec2(container_width_, container_height_);
  ci::Rectf container_box(top_left_corner_, pixel_bottom_right);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(container_box);

  //draw particles inside container
  for (const ParticleGroup& group: particle_groups_) {
    for (size_t index = 0; index < group.GetGroupSize(); index++) {
      Particle current_particle = group.GetParticleAt(index);
      size_t radius = current_particle.radius;
      vec2 screen_position = current_particle.position + top_left_corner_ +
                             vec2(radius, radius);
      ci::gl::color(ci::Color(current_particle.color));
      ci::gl::drawSolidCircle(screen_position, current_particle.radius);
    }
  }
}

} // namespace visualizer

} // namespace idealgas