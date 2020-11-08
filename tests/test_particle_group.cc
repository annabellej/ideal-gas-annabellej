#include <catch2/catch.hpp>
#include "core/particle_group.h"
#include "core/particle_utils.h"

using namespace idealgas;
using namespace idealgas::particleutils;

//TODO: delete this scratchwork test
TEST_CASE("Scratch") {
  Particle* p1 = new Particle(vec2(50.0,50.0), vec2(1.0,0.0), 2, 5, "cyan");
  Particle* p2 = new Particle(vec2(65.0,50.0), vec2(-1.0,0.0), 15, 20, "magenta");

  HandleParticleCollision(p1, p2);

  REQUIRE(p1->velocity.x == Approx(-2));
  REQUIRE(p1->velocity.y == Approx(0));

  delete p1;
  delete p2;
}