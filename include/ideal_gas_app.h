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

    const double kWindowSize = 900;
    const size_t kContainerDimension = 100;
    const size_t kNumberParticles = 10;

  private:
    Simulator simulator_;
};

} // namespace visualizer

} // namepsace idealgas