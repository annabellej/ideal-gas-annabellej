#include "core/ideal_gas_histogram.h"

namespace idealgas {

IdealGasHistogram::~IdealGasHistogram() {
  delete particle_group_;
}

void IdealGasHistogram::DrawHistogram() const {
  DrawHistogramBox();
  vec2 bottom_left = top_left_ + vec2(0,histogram_height_);
  DrawHistogramBars(bottom_left);
}

void IdealGasHistogram::DrawHistogramBox() const {
  //draw box
  ci::Rectf histogram_box(top_left_, bottom_right_);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(histogram_box);

  //draw horizontal axis label
  ci::gl::drawStringCentered("Speed",vec2(bottom_right_.x-(histogram_width_/2),
                                          bottom_right_.y+display_margin_/10));
  //draw vertical axis label
  //method to rotate text from: https://discourse.libcinder.org/t/what-is-the-best-way-to-rotate-rectangles-images/410/2
  ci::gl::pushModelMatrix();
  ci::gl::translate(top_left_.x-display_margin_/10,
                    top_left_.y+histogram_height_/2+35);
  ci::gl::rotate(3*M_PI/2);
  ci::gl::drawString("Particle Count", vec2(0,0));
  ci::gl::popModelMatrix();
}

void IdealGasHistogram::DrawHistogramBars(vec2 bottom_left) const {
  //create list of all speeds in this particle group
  vector<double> particle_speeds;
  for (size_t index = 0; index < particle_group_->GetGroupSize(); ++index) {
    particle_speeds.push_back(glm::length(particle_group_->GetParticleAt(index)->velocity));
  }
  std::sort(particle_speeds.begin(), particle_speeds.end());

  //get speed value intervals for histogram buckets
  vector<double> bucket_speed_limits; //upper limit of each bucket in histogram
  double bucket_size = (particle_speeds.back() - particle_speeds.front()) / bucket_count_;
  for (size_t index = 0; index < bucket_count_; ++index) {
    if (index == 0) {
      bucket_speed_limits.push_back(particle_speeds.front() + bucket_size);
    } else {
      bucket_speed_limits.push_back(bucket_speed_limits.back() + bucket_size);
    }
  }

  //get number of particles in each histogram bucket
  vector<size_t> particles_per_bucket(bucket_count_, 0);
  for (double speed: particle_speeds) {
    for (size_t index = 0; index < bucket_count_; ++index) {
      double limit = bucket_speed_limits.at(index);
      if (speed <= limit) {
        particles_per_bucket.at(index)++;
        break;
      }
    }
  }

  //draw bars based on particle count for each bucket
  ci::gl::color(particle_group_->GetGroupColor());
  int pixel_bucket_size = histogram_width_ / bucket_count_;
  vec2 current_top_left = vec2(bottom_left.x - pixel_bucket_size, bottom_left.y);

  for (size_t count: particles_per_bucket) {
    int bar_height = count * y_interval_pixels_;
    current_top_left = vec2(current_top_left.x + pixel_bucket_size, bottom_left.y - bar_height);
    vec2 bottom_right = vec2(current_top_left.x + pixel_bucket_size, bottom_left.y);
    ci::Rectf bar_box(current_top_left, bottom_right);
    ci::gl::drawSolidRect(bar_box);
  }
}

} // namespace idealgas