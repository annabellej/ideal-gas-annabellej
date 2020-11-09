#pragma once

#include <vector>
#include <map>
#include "core/particle.h"
#include "core/particle_group.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

using std::vector;
using std::map;
using glm::vec2;

/**
 * A IdealGasSimulator that visualizes the motion of a number of ideal gas particles
 * inside a container over time.
 */
class IdealGasSimulator {
  public:
    /**
     * Default constructor for an Ideal Gas Simulator.
     */
    IdealGasSimulator() = default;

    /**
     * Constructor for an Ideal Gas Simulator with multiple particle types.
     *
     * @param top_left_corner       coordinates of container's top left corner.
     *
     * @param particle_information  map w/ particle info + count
     *
     * @param container_width       the width in pixels of the container.
     * @param container_height      the height in pixels of the container.
     * @param histogram_width       the width in pixels of histograms.
     * @param histogram_height      the height in pixels of histograms.
     *
     * @param display_margin        pixel count for margins of display.
     *
     * @param num_buckets           number of buckets for histogram displays.
     * @param y_interval            pixels in one y axis interval on histogram.
     */
    IdealGasSimulator(const vec2& top_left_corner,
                      const map<Particle, size_t>& particle_information,
                      size_t container_width, size_t container_height,
                      size_t histogram_width, size_t histogram_height,
                      size_t display_margin, size_t num_buckets,
                      size_t y_interval);

    /**
     * Updates the particles' movement after one unit of time.
     */
    void Update();

    /**
     * Displays the current state of the particles in the Cinder application.
     */
    void Draw() const;

  private:
    vec2 top_left_corner_;
    size_t container_width_;
    size_t container_height_;
    size_t display_margin_;

    //histogram details
    size_t histogram_width_;
    size_t histogram_height_;
    size_t bucket_count_;
    size_t y_interval_pixels_;

    vector<ParticleGroup*> particle_groups_;

    /**
     * Updates movements of all particles in all groups based on possible
     * collisions between any particles. Helper method for updating.
     */
    void HandleAllParticleCollisions();

    /**
     * Draws histograms for all particle groups on display.
     */
    void DrawHistograms() const;

    /**
     * Draws the outline and axes for a histogram.
     *
     * @param top_left      vector denoting top left corner of histogram.
     * @param bottom_right  vector denoting bottom right corner of histogram.
     */
    void DrawHistogramBox(vec2 top_left, vec2 bottom_right) const;

    /**
     * Draws the bars of a histogram based on a group of particles.
     *
     * @param particle_group the group of particles to analyze.
     * @param bottom_left vector denoting bottom left corner of histogram to
     *                    draw the bars for.
     */
    void DrawHistogramBars(ParticleGroup* particle_group, vec2 bottom_left) const;
};

} // namespace visualizer

} // namespace idealgas