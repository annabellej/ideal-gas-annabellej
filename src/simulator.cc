#include "simulator.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

using glm::vec2;

Simulator::Simulator(const vec2 &top_left_corner, size_t number_particles,
                     size_t container_width, size_t container_height,
                     size_t particle_mass, size_t particle_radius,
                     const ci::Color& particle_color) {
  top_left_corner_ = top_left_corner;
  container_width_ = container_width;
  container_height_ = container_height;

  //generate given number of random particles
  size_t max_x_position = container_width_ - particle_radius * 2;
  size_t max_y_position = container_height_ - particle_radius * 2;
  int max_velocity_magnitude = particle_radius / 2;

  for (int index = 0; index < number_particles; index++) {
    //generate random position
    double x_position = GenerateRandomDouble((double) max_x_position, 0.0);
    double y_position = GenerateRandomDouble((double) max_y_position, 0.0);
    vec2 particle_position(x_position, y_position);

    //generate random velocity
    double x_velocity = GenerateRandomDouble((double) max_velocity_magnitude,
                                             (double) -max_velocity_magnitude);
    double y_velocity = GenerateRandomDouble((double) max_velocity_magnitude,
                                             (double) -max_velocity_magnitude);
    vec2 particle_velocity(x_velocity, y_velocity);

    //add new particle to vector of particles
    particles_.push_back(Particle(particle_position, particle_velocity,
                               particle_mass, particle_radius, particle_color));
  }
}

void Simulator::Update() {
  for (Particle& particle: particles_) {
    //check if collision happens


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
    ci::gl::drawSolidCircle(screen_position, particle.radius);
  }
}

double Simulator::GenerateRandomDouble(double max_value, double min_value) const {
  return (max_value - min_value) * (double) rand() / (double) RAND_MAX;
}

} // namespace visualizer

} // namespace idealgas