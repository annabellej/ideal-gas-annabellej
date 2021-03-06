#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ideal_gas_simulator.h"

namespace idealgas {

namespace visualizer {

/**
 * Displays the motion of ideal gas particles in a container over time.
 */
class IdealGasApp : public ci::app::App {
  public:
    /**
     * Default constructor for an Ideal Gas App.
     */
    IdealGasApp();

    void update() override;
    void draw() override;

    //constants for display window dimensions
    const size_t kWindowSize = 1000;
    const size_t kMargin = 50;
    //constants for container/histogram dimensions
    const size_t kContainerWidth = 600;
    const size_t kContainerHeight = 800;
    const size_t kHistogramWidth = 250;
    const size_t kHistogramHeight = 200;
    const size_t kNumBuckets = 10;
    const size_t kYIntervalPixels = 2;

    //constants for particles
    const size_t kSmallParticlesCount = 200;
    const size_t kSmallParticleMass = 2;
    const size_t kSmallParticleRadius = 5;
    const ci::Color kSmallParticleColor = "yellow";

    const size_t kMidParticlesCount = 75;
    const size_t kMidParticleMass = 5;
    const size_t kMidParticleRadius = 10;
    const ci::Color kMidParticleColor = "magenta";

    const size_t kBigParticlesCount = 30;
    const size_t kBigParticleMass = 15;
    const size_t kBigParticleRadius = 15;
    const ci::Color kBigParticleColor = "cyan";

  private:
    IdealGasSimulator simulator_;
};

} // namespace visualizer

} // namespace idealgas