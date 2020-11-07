#include "visualizer/ideal_gas_simulator.h"
#include "core/particle.h"
#include "cinder/gl/gl.h"
#include <catch2/catch.hpp>

using glm::vec2;
using idealgas::visualizer::IdealGasSimulator;
using idealgas::Particle;

IdealGasSimulator test_simulator(vec2(100,100), 0, 200, 200, 1, 4, "white");

bool AreVectorsEqual(vec2 first, vec2 second) {
  return (double) first.x == Approx((double) second.x) &&
         (double) first.y == Approx((double) second.y);
}

TEST_CASE("Particles move correctly when no collision happens") {
  SECTION("Particle position changes correctly based on velocity") {
    Particle test_particle(vec2(50.0,50.0), vec2(0.4,0.5), 1, 1, "white");
    test_simulator.AddParticle(test_particle);
    test_simulator.Update();

    REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).position,
                            vec2(50.4,50.5)));
  }

  SECTION("Particle position should not change if initial velocity is 0,0") {
    Particle no_velocity_particle(vec2(50.0,50.0), vec2(0.0,0.0), 1, 1, "white");
    test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
    test_simulator.AddParticle(no_velocity_particle);
    test_simulator.Update();

    REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).position,
                            vec2(50.0,50.0)));
  }
}

TEST_CASE("Particles move correctly when colliding with wall") {
  SECTION("Touching top wall") {
    SECTION("Moving away from wall does not collide") {
      Particle test_particle(vec2(50.0,0.0), vec2(0.4,0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity does NOT change
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).velocity,
                              vec2(0.4,0.5)));
      //check position properly updates
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).position,
                              vec2(50.4,0.5)));
    }

    SECTION("Colliding w/ wall negates y component of velocity") {
      Particle test_particle(vec2(50.0,0.0), vec2(0.4,-0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity properly updates
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).velocity,
                             vec2(0.4,0.5)));
      //check position properly updates
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).position,
                              vec2(50.4,0.5)));
    }
  }

  SECTION("Touching bottom wall") {
    SECTION("Moving away from wall does not collide") {
      Particle test_particle(vec2(50.0,198.0), vec2(0.4,-0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity does NOT change
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).velocity,
                              vec2(0.4,-0.5)));
      //check position properly updates
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).position,
                              vec2(50.4,197.5)));
    }

    SECTION("Colliding w/ wall negates y component of velocity") {
      Particle test_particle(vec2(50.0,198.0), vec2(0.4,0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity properly updates
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).velocity,
                              vec2(0.4,-0.5)));
      //check position properly updates
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).position,
                              vec2(50.4,197.5)));
    }
  }

  SECTION("Touching left wall") {
    SECTION("Moving away from wall does not collide") {
      Particle test_particle(vec2(0.0,50.0), vec2(0.4,0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity does NOT change
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).velocity,
                              vec2(0.4,0.5)));
      //check position properly updates
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).position,
                              vec2(0.4,50.5)));
    }

    SECTION("Colliding w/ wall negates x component of velocity") {
      Particle test_particle(vec2(0.0,50.0), vec2(-0.4,0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity properly updates
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).velocity,
                              vec2(0.4,0.5)));
      //check position properly updates
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).position,
                              vec2(0.4,50.5)));
    }
  }

  SECTION("Touching right wall") {
    SECTION("Moving away from wall does not collide") {
      Particle test_particle(vec2(198.0,50.0), vec2(-0.4,0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity does NOT change
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).velocity,
                              vec2(-0.4,0.5)));
      //check position properly updates
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).position,
                              vec2(197.6,50.5)));
    }

    SECTION("Colliding w/ wall negates x component of velocity") {
      Particle test_particle(vec2(198.0,50.0), vec2(0.4,0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity properly updates
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).velocity,
                              vec2(-0.4,0.5)));
      //check position properly updates
      REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).position,
                              vec2(197.6,50.5)));
    }
  }
}

TEST_CASE("Particles move correctly when colliding with another particle") {
  SECTION("Particles moving away from each other do not collide") {
    Particle first_particle(vec2(50.0,50.0), vec2(-1.0,-1.0), 1, 1, "white");
    Particle second_particle(vec2(52.0,50.0), vec2(1.0,1.0), 1, 1, "white");

    test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
    test_simulator.AddParticle(first_particle);
    test_simulator.AddParticle(second_particle);
    test_simulator.Update();

    //check velocities do NOT change
    REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).velocity,
                            vec2(-1.0,-1.0)));
    REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(1).velocity,
                            vec2(1.0,1.0)));
  }

  SECTION("Particle colliding w/ another correctly change velocity") {
    Particle first_particle(vec2(50.0,50.0), vec2(1.0,1.0), 1, 1, "white");
    Particle second_particle(vec2(52.0,50.0), vec2(-1.0,-1.0), 1, 1, "white");

    test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
    test_simulator.AddParticle(first_particle);
    test_simulator.AddParticle(second_particle);
    test_simulator.Update();

    //check velocities properly update
    REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).velocity,
                            vec2(-1.0,1.0)));
    REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(1).velocity,
                            vec2(1.0,-1.0)));
  }

  SECTION("Pairs of particles collide correctly with >2 particles in box") {
    Particle first_particle(vec2(50.0,50.0), vec2(1.0,1.0), 1, 1, "white");
    Particle second_particle(vec2(52.0,50.0), vec2(-1.0,-1.0), 1, 1, "white");
    Particle third_particle(vec2(35.0,40.0), vec2(0.4,0.6), 1, 1, "white");
    Particle fourth_particle(vec2(0.0,2.0), vec2(0.3,-1.0), 1, 1, "white");

    test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
    test_simulator.AddParticle(first_particle);
    test_simulator.AddParticle(second_particle);
    test_simulator.AddParticle(third_particle);
    test_simulator.AddParticle(fourth_particle);
    test_simulator.Update();

    //check only velocities of first two particles change from their collision
    REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(0).velocity,
                            vec2(-1.0,1.0)));
    REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(1).velocity,
                            vec2(1.0,-1.0)));
    REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(2).velocity,
                            vec2(0.4,0.6)));
    REQUIRE(AreVectorsEqual(test_simulator.GetParticleAt(3).velocity,
                            vec2(0.3,-1.0)));
  }
}