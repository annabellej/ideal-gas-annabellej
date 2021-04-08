#include "visualizer/ideal_gas_simulator.h"
#include "cinder/gl/gl.h"
#include "core/particle_utils.h"
#include "core/ideal_gas_histogram.h"
#include <math.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;
using glm::length;
using glm::dot;

using idealgas::particleutils::ParticleCollisionExists;
using idealgas::particleutils::HandleParticleCollision;
using idealgas::IdealGasHistogram;

IdealGasSimulator::IdealGasSimulator(const vec2 &top_left_corner,
                                     const map<Particle, size_t> &particle_information,
                                     size_t container_width, size_t container_height,
                                     size_t histogram_width, size_t histogram_height,
                                     size_t display_margin, size_t num_buckets,
                                     size_t y_interval) {
  top_left_corner_ = top_left_corner;
  container_width_ = container_width;
  container_height_ = container_height;
  histogram_width_ = histogram_width;
  histogram_height_ = histogram_height;
  bucket_count_ = num_buckets;
  y_interval_pixels_ = y_interval;
  display_margin_ = display_margin;

  for (auto const& entry: particle_information) {
    size_t num_particles = entry.second;
    size_t mass = entry.first.mass;
    size_t radius = entry.first.radius;
    ci::Color color = entry.first.color;

    double max_x_position = (double) container_width - radius * 2;
    double max_y_position = (double) container_height - radius * 2;
    double max_velocity = radius * (1.0 / mass); //v is relatively small

    particle_groups_.push_back(new ParticleGroup(num_particles, mass, radius,
                                                 color, max_x_position,
                                                 max_y_position, max_velocity));
  }
}

IdealGasSimulator::IdealGasSimulator(const vec2& top_left_corner,
                                     const vector<ParticleGroup*>& groups,
                                     size_t container_width, size_t container_height,
                                     size_t histogram_width, size_t histogram_height,
                                     size_t display_margin, size_t num_buckets,
                                     size_t y_interval) {
  particle_groups_ = groups;
  top_left_corner_ = top_left_corner;
  container_width_ = container_width;
  container_height_ = container_height;
  histogram_width_ = histogram_width;
  histogram_height_ = histogram_height;
  bucket_count_ = num_buckets;
  y_interval_pixels_ = y_interval;
  display_margin_ = display_margin;
}

void IdealGasSimulator::Update() {
  //update particles/walls colliding
  for (ParticleGroup* group: particle_groups_) {
    group->HandlePossibleWallCollisions();
  }

  //update particles colliding
  HandleAllParticleCollisions();

  //update all particle positions
  for (ParticleGroup* group: particle_groups_) {
    group->UpdatePositions();
  }
}

void IdealGasSimulator::Draw() const {
  //draw rectangular container for particles
  vec2 pixel_bottom_right = top_left_corner_ +
                            vec2(container_width_, container_height_);
  ci::Rectf container_box(top_left_corner_, pixel_bottom_right);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(container_box);

  //draw particles and histograms
  DrawParticles();
  DrawHistograms();
}

void IdealGasSimulator::HandleAllParticleCollisions() {
  //make list of all particles from all groups
  vector<Particle*> all_particles = ListAllParticles();
  //make bool list to keep track of already updated
  vector<bool> updated_particles(all_particles.size(), false);

  //go through particle list and handle collisions between any of them
  for (size_t index = 0; index < all_particles.size(); index++) {
    if (updated_particles.at(index)) {
      continue;
    }
    Particle* first_particle = all_particles.at(index);
    for (size_t other_index = 0; other_index < all_particles.size() &&
                                 other_index != index; other_index++) {
      Particle* second_particle = all_particles.at(other_index);
      if (ParticleCollisionExists(*first_particle, *second_particle)) {
        Particle& first = *first_particle;
        Particle& second = *second_particle;
        Particle temp(first.position, first.velocity, first.mass, first.radius,
                      first.color);

        HandleParticleCollision(first, second);
        HandleParticleCollision(second, temp);
        updated_particles.at(other_index) = true;
      }
    }
  }
}

void IdealGasSimulator::DrawParticles() const {
  for (ParticleGroup* group: particle_groups_) {
    for (size_t index = 0; index < group->GetGroupSize(); index++) {
      Particle current_particle = *group->GetParticleAt(index);
      size_t radius = current_particle.radius;
      vec2 screen_position = current_particle.position + top_left_corner_ +
                             vec2(radius, radius);
      ci::gl::color(ci::Color(current_particle.color));
      ci::gl::drawSolidCircle(screen_position, current_particle.radius);
    }
  }
}

void IdealGasSimulator::DrawHistograms() const {
  vec2 bottom_right;
  vec2 top_left = top_left_corner_ + vec2(container_width_,0) +
                  vec2(display_margin_,0) - vec2(0, histogram_height_ + display_margin_);

  for (ParticleGroup* group: particle_groups_) {
    top_left = top_left + vec2(0, histogram_height_ + display_margin_);
    bottom_right = top_left + vec2(histogram_width_, histogram_height_);

    IdealGasHistogram* histogram = new IdealGasHistogram(top_left, bottom_right, group,
                                            histogram_width_, histogram_height_,
                                            display_margin_, bucket_count_,
                                            y_interval_pixels_);
    histogram->DrawHistogram();
  }
}

vector<Particle*> IdealGasSimulator::ListAllParticles() const {
  vector<Particle*> all_particles;

  for (ParticleGroup* group: particle_groups_) {
    for (size_t index = 0; index < group->GetGroupSize(); index++) {
      Particle* current_particle = group->GetParticleAt(index);
      all_particles.push_back(current_particle);
    }
  }

  return all_particles;
}

} // namespace visualizer

} // namespace idealgas