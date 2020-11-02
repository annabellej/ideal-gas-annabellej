#include "ideal_gas_app.h"

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp() : simulator_(glm::vec2(kMargin, kMargin),
                                        kNumParticles, kContainerWidth,
                                        kContainerHeight, kParticleMass,
                                        kParticleRadius, kParticleColor) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
};

void IdealGasApp::update() {
  simulator_.Update();
}

void IdealGasApp::draw() {
  ci::Color8u background_color(0,0,0); //black
  ci::gl::clear(background_color);

  simulator_.Draw();
}

} // namespace visualizer

} // idealgas