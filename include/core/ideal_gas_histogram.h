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
     * @param num_buckets   number of buckets in this histogram (x-axes intervals).
     * @param y_interval_size number of pixels for each y axis interval.
     */
    IdealGasHistogram(const vec2& top_left, const vec2& bottom_right,
                      ParticleGroup* particles, size_t width,
                      size_t height, size_t margins, size_t num_buckets,
                      size_t y_interval_size);

    /**
     * Destructor for an ideal gas histogram.
     */
    ~IdealGasHistogram();

    /**
     * Draws the histogram for the current particles and their speeds.
     */
    void DrawHistogram() const;

    /**
     * Fetches the particle speed at the given index in the list of particle
     * speeds.
     *
     * @param index the index of the speed to retrieve.
     *
     * @return the speed at the given position.
     */
    double GetParticleSpeedAt(size_t index) const;

    /**
     * Fetches the upper speed limit of a given bucket.
     *
     * @param index the bucket index to retrieve the upper limit of.
     *
     * @return the upper speed limit of the given bucket index.
     */
    double GetBucketLimitAt(size_t index) const;

    /**
     * Fetches the number of particles in a particular bucket.
     *
     * @param index the bucket index to find the particle count of.
     *
     * @return the number of particles in the given bucket.
     */
    size_t GetNumberParticlesAt(size_t index) const;

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

    vector<double> particle_speeds_;     //stores all sorted particle speeds
    vector<double> bucket_speed_limits_; //stores upper speed limits of buckets
    vector<size_t> particles_per_bucket_; //stores particle count per bucket

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

    /**
     * Creates a vector listing all the sorted speeds of the particles.
     */
    void ListSortedParticleSpeeds();

    /**
     * Finds the upper speed limit for each bucket of the histogram based on
     * the speeds of all particles.
     */
    void CalculateBucketSpeedLimits();

    /**
     * Counts the number of particles in the group that fit in each histogram
     * bucket based on their speeds.
     */
    void CountParticlesPerBucket();
};

} // namespace idealgas