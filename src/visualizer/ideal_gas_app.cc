#include "visualizer/ideal_gas_app.h"
#include <map>

namespace idealgas {

namespace visualizer {

using std::map;

IdealGasApp::IdealGasApp() {
  //add small, mid, and big particle information into a map
  map<Particle, size_t> particle_information;
  Particle arbitrary_small_particle(vec2(0,0), vec2(0,0),
                                    kSmallParticleMass, kSmallParticleRadius,
                                    kSmallParticleColor);
  Particle arbitrary_mid_particle(vec2(0,0), vec2(0,0),
                                    kMidParticleMass, kMidParticleRadius,
                                    kMidParticleColor);
  Particle arbitrary_big_particle(vec2(0,0), vec2(0,0),
                                    kBigParticleMass, kBigParticleRadius,
                                    kBigParticleColor);
  particle_information.insert(std::pair<Particle, size_t>(arbitrary_small_particle,
                                                          kSmallParticlesCount));
  particle_information.insert(std::pair<Particle, size_t>(arbitrary_mid_particle,
                                                          kMidParticlesCount));
  particle_information.insert(std::pair<Particle, size_t>(arbitrary_big_particle,
                                                          kBigParticlesCount));
  //initialize simulator and set up display window
  simulator_ = IdealGasSimulator(vec2(kMargin, kMargin),
                                 particle_information, kContainerWidth,
                                 kContainerHeight);
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