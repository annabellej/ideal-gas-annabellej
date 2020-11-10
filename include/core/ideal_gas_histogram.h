#pragma once

#include "cinder/gl/gl.h"
#include "core/particle_group.h"

using glm::vec2;
using idealgas::ParticleGroup;

namespace idealgas {

/**
 * A histogram representing the speed distribution of a certain group of ideal
 * gas particles.
 */
class IdealGasHistogram {
  public:
    /**
     * A histogram illustrating the speeds of a group of particles.
     *
     * @param top_left      coordinates of the top left position of graph.
     * @param bottom_right  coordinates of the bottom right position of graph.
     *
     * @param particles     the group of particles to analyze and display.
     *
     * @param margins       size in pixels of margins used in display.
     * @param width         width in pixels of the histogram.
     * @param height        height in pixels of the histogram.
     * @param num_buckets   number of buckets in this histogram.
     * @param y_interval_size number of pixels for each y axis interval.
     */
    IdealGasHistogram(const vec2& top_left, const vec2& bottom_right,
                      ParticleGroup* particles, size_t width,
                      size_t height, size_t margins, size_t num_buckets,
                      size_t y_interval_size) : top_left_(top_left),
                      bottom_right_(bottom_right), display_margin_(margins),
                      histogram_width_(width), histogram_height_(height),
                      bucket_count_(num_buckets), y_interval_pixels_(y_interval_size),
                      particle_group_(particles) {};

    /**
     * Destructor for an ideal gas histogram.
     */
    ~IdealGasHistogram();

    /**
     * Draws the histogram for the current particles and their speeds.
     */
    void DrawHistogram() const;

  private:
    //corner positions of histogram on display
    vec2 top_left_;
    vec2 bottom_right_;

    //histogram dimension values
    size_t display_margin_;
    size_t histogram_width_;
    size_t histogram_height_;
    size_t bucket_count_;
    size_t y_interval_pixels_;

    ParticleGroup* particle_group_;

    /**
     * Draws the outline and axes of the histogram on the display.
     */
    void DrawHistogramBox() const;

    /**
     * Draws the bars of the histogram based on the velocities of the particles.
     *
     * @param bottom_left   bottom left corner position of the histogram.
     */
    void DrawHistogramBars(vec2 bottom_left) const;
};

} // namespace idealgas