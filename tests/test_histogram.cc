#include <catch2/catch.hpp>
#include "core/ideal_gas_histogram.h"
#include "core/particle.h"

using idealgas::IdealGasHistogram;
using idealgas::Particle;

TEST_CASE("Histogram functions correctly") {
  //initiate particle group and histogram to test
  ParticleGroup* test_group = new ParticleGroup(0, 1, 4, "white", 100.0,100.0,1.0);

  Particle first_particle(vec2(50.0,50.0), vec2(0.0,1.0), 1, 4, "white"); //speed = 1
  Particle second_particle(vec2(30.0,30.0), vec2(2.0,0.0), 1, 4, "white");//speed = 2
  Particle third_particle(vec2(10.0,10.0), vec2(0.0,-3.0), 1, 4, "white");//speed = 3
  Particle fourth_particle(vec2(70.0,70.0), vec2(0.5,0.0), 1, 4, "white");//speed = 0.5

  test_group->AddParticle(first_particle);
  test_group->AddParticle(second_particle);
  test_group->AddParticle(third_particle);
  test_group->AddParticle(fourth_particle);

  IdealGasHistogram* test_histogram = new IdealGasHistogram(vec2(0.0,0.0),
                                                            vec2(100.0,100.0),
                                                            test_group,250,200,
                                                            50,4,2);

  SECTION("Constructor produces properly sorted list of particle speeds") {
    for (int index = 1; index < 4; index++) {
      REQUIRE(test_histogram->GetParticleSpeedAt(index) >=
              test_histogram->GetParticleSpeedAt(index-1));
    }
  }

  SECTION("Calculated histogram bucket intervals are correct") {
    REQUIRE(test_histogram->GetBucketLimitAt(0) == Approx(1.125));
    REQUIRE(test_histogram->GetBucketLimitAt(1) == Approx(1.75));
    REQUIRE(test_histogram->GetBucketLimitAt(2) == Approx(2.375));
    REQUIRE(test_histogram->GetBucketLimitAt(3) == Approx(3.0));
  }

  SECTION("Number of particles in each bucket calculated correctly") {
    REQUIRE(test_histogram->GetNumberParticlesAt(0) == 2);
    REQUIRE(test_histogram->GetNumberParticlesAt(1) == 0);
    REQUIRE(test_histogram->GetNumberParticlesAt(2) == 1);
    REQUIRE(test_histogram->GetNumberParticlesAt(3) == 1);
  }
}