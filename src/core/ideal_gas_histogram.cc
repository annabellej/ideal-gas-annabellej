#include "core/ideal_gas_histogram.h"

namespace idealgas {

IdealGasHistogram::IdealGasHistogram(const vec2 &top_left,
                                     const vec2 &bottom_right,
                                     ParticleGroup *particles, size_t width,
                                     size_t height, size_t margins,
                                     size_t num_buckets,
                                     size_t y_interval_size) {
  top_left_ = top_left;
  bottom_right_ = bottom_right;
  display_margin_ = margins;
  histogram_width_ = width;
  histogram_height_ = height;
  bucket_count_ = num_buckets;
  y_interval_pixels_ = y_interval_size;
  particle_group_ = particles;

  ListSortedParticleSpeeds();
  CalculateBucketSpeedLimits();

  //number of particles for each bucket of histogram starts at 0
  particles_per_bucket_ = vector<size_t>(bucket_count_, 0);

  CountParticlesPerBucket();
}

IdealGasHistogram::~IdealGasHistogram() {
  delete particle_group_;
}

void IdealGasHistogram::DrawHistogram() const {
  DrawHistogramBox();
  vec2 bottom_left = top_left_ + vec2(0,histogram_height_);
  DrawHistogramBars(bottom_left);
}

double IdealGasHistogram::GetParticleSpeedAt(size_t index) const {
  return particle_speeds_.at(index);
}

double IdealGasHistogram::GetBucketLimitAt(size_t index) const {
  return bucket_speed_limits_.at(index);
}

size_t IdealGasHistogram::GetNumberParticlesAt(size_t index) const {
  return particles_per_bucket_.at(index);
}

void IdealGasHistogram::DrawHistogramBox() const {
  //draw box
  ci::Rectf histogram_box(top_left_, bottom_right_);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(histogram_box);

  //draw horizontal axis label
  ci::gl::drawStringCentered("Speed", vec2(bottom_right_.x-(histogram_width_/2),
                                           bottom_right_.y+display_margin_/10));
  //draw vertical axis label
  //method to rotate text from: https://discourse.libcinder.org/t/what-is-the-best-way-to-rotate-rectangles-images/410/2
  ci::gl::pushModelMatrix();
  ci::gl::translate(top_left_.x - display_margin_ / 10,
                    top_left_.y + histogram_height_ / 2);
  ci::gl::rotate(3 * M_PI / 2);
  ci::gl::drawStringCentered("Particle Count", vec2(0,0));
  ci::gl::popModelMatrix();
}

void IdealGasHistogram::DrawHistogramBars(vec2 bottom_left) const {
  //draw bars based on particle count for each bucket
  ci::gl::color(particle_group_->GetGroupColor());
  int pixel_bucket_size = histogram_width_ / bucket_count_;
  vec2 current_top_left = vec2(bottom_left.x - pixel_bucket_size, bottom_left.y);

  for (size_t count: particles_per_bucket_) {
    int bar_height = count * y_interval_pixels_;

    current_top_left = vec2(current_top_left.x + pixel_bucket_size,
                            bottom_left.y - bar_height);
    vec2 bottom_right = vec2(current_top_left.x + pixel_bucket_size,
                             bottom_left.y);

    ci::Rectf bar_box(current_top_left, bottom_right);
    ci::gl::drawSolidRect(bar_box);
  }
}

void IdealGasHistogram::ListSortedParticleSpeeds() {
  for (size_t index = 0; index < particle_group_->GetGroupSize(); ++index) {
    particle_speeds_.push_back(glm::length(particle_group_->
                                           GetParticleAt(index)->velocity));
  }
  std::sort(particle_speeds_.begin(), particle_speeds_.end());
}

void IdealGasHistogram::CalculateBucketSpeedLimits() {
  //calculate speed range for each bucket
  double bucket_size = (particle_speeds_.back() - particle_speeds_.front()) /
                        bucket_count_;

  //loop through buckets, calculate upper speed limit for each
  for (size_t index = 0; index < bucket_count_; ++index) {
    if (index == 0) {
      bucket_speed_limits_.push_back(particle_speeds_.front() + bucket_size);
    } else {
      bucket_speed_limits_.push_back(bucket_speed_limits_.back() + bucket_size);
    }
  }
}

void IdealGasHistogram::CountParticlesPerBucket() {
  //loop through particles' speeds, checks which bucket each speed belongs in
  for (double speed: particle_speeds_) {
    for (size_t index = 0; index < bucket_count_; ++index) {
      double upper_limit = bucket_speed_limits_.at(index);

      if (speed <= upper_limit) {
        particles_per_bucket_.at(index)++;
        break;
      }
    }
  }
}

} // namespace idealgas