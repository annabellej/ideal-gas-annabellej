#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "simulator.h"

namespace idealgas {

namespace visualizer {

/**
 * Displays the motion of ideal gas particles in a container over time.
 */
class IdealGasApp : public ci::app::App {
  public:
    IdealGasApp();

    void update() override;
    void draw() override;

    const double kWindowSize = 1000;
    const double kMargin = 50;
    const size_t kContainerWidth = 600;
    const size_t kContainerHeight = 800;
    const size_t kNumParticles = 10;

  private:
    Simulator simulator_;
};

} // namespace visualizer

} // namepsace idealgas