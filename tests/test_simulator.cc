#include "simulator.h"
#include "particle.h"
#include "cinder/gl/gl.h"
#include <catch2/catch.hpp>

using glm::vec2;
using idealgas::visualizer::Simulator;
using idealgas::Particle;

Simulator test_simulator(vec2(100,100), 0, 200, 200, 1, 4, "white");

TEST_CASE("Particles move correctly when no collision happens") {
  SECTION("Particle position changes correctly based on velocity") {
    Particle test_particle(vec2(50.0,50.0), vec2(0.4,0.5), 1, 1, "white");
    test_simulator.AddParticle(test_particle);
    test_simulator.Update();

    REQUIRE((double) test_simulator.GetParticleAt(0).position.x == Approx(50.4));
    REQUIRE((double) test_simulator.GetParticleAt(0).position.y == Approx(50.5));
  }

  SECTION("Particle position should not change if initial velocity is 0,0") {
    Particle no_velocity_particle(vec2(50.0,50.0), vec2(0.0,0.0), 1, 1, "white");
    test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
    test_simulator.AddParticle(no_velocity_particle);
    test_simulator.Update();

    REQUIRE((double) test_simulator.GetParticleAt(0).position.x == Approx(50.0));
    REQUIRE((double) test_simulator.GetParticleAt(0).position.y == Approx(50.0));
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
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.x==Approx(0.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.y==Approx(0.5));

      //check position properly updates
      REQUIRE((double)test_simulator.GetParticleAt(0).position.x==Approx(50.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).position.y==Approx(0.5));
    }

    SECTION("Colliding w/ wall negates y component of velocity") {
      Particle test_particle(vec2(50.0,0.0), vec2(0.4,-0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity properly updates
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.x==Approx(0.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.y==Approx(0.5));

      //check position properly updates
      REQUIRE((double)test_simulator.GetParticleAt(0).position.x==Approx(50.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).position.y==Approx(0.5));
    }
  }

  SECTION("Touching bottom wall") {
    SECTION("Moving away from wall does not collide") {
      Particle test_particle(vec2(50.0,198.0), vec2(0.4,-0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity does NOT change
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.x==Approx(0.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.y==Approx(-0.5));

      //check position properly updates
      REQUIRE((double)test_simulator.GetParticleAt(0).position.x==Approx(50.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).position.y==Approx(197.5));
    }

    SECTION("Colliding w/ wall negates y component of velocity") {
      Particle test_particle(vec2(50.0,198.0), vec2(0.4,0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity properly updates
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.x==Approx(0.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.y==Approx(-0.5));

      //check position properly updates
      REQUIRE((double)test_simulator.GetParticleAt(0).position.x==Approx(50.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).position.y==Approx(197.5));
    }
  }

  SECTION("Touching left wall") {
    SECTION("Moving away from wall does not collide") {
      Particle test_particle(vec2(0.0,50.0), vec2(0.4,0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity does NOT change
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.x==Approx(0.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.y==Approx(0.5));

      //check position properly updates
      REQUIRE((double)test_simulator.GetParticleAt(0).position.x==Approx(0.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).position.y==Approx(50.5));
    }

    SECTION("Colliding w/ wall negates x component of velocity") {
      Particle test_particle(vec2(0.0,50.0), vec2(-0.4,0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity properly updates
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.x==Approx(0.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.y==Approx(0.5));

      //check position properly updates
      REQUIRE((double)test_simulator.GetParticleAt(0).position.x==Approx(0.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).position.y==Approx(50.5));
    }
  }

  SECTION("Touching right wall") {
    SECTION("Moving away from wall does not collide") {
      Particle test_particle(vec2(198.0,50.0), vec2(-0.4,0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity does NOT change
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.x==Approx(-0.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.y==Approx(0.5));

      //check position properly updates
      REQUIRE((double)test_simulator.GetParticleAt(0).position.x==Approx(197.6));
      REQUIRE((double)test_simulator.GetParticleAt(0).position.y==Approx(50.5));
    }

    SECTION("Colliding w/ wall negates x component of velocity") {
      Particle test_particle(vec2(198.0,50.0), vec2(0.4,0.5), 1, 1, "white");
      test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
      test_simulator.AddParticle(test_particle);
      test_simulator.Update();

      //check velocity properly updates
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.x==Approx(-0.4));
      REQUIRE((double)test_simulator.GetParticleAt(0).velocity.y==Approx(0.5));

      //check position properly updates
      REQUIRE((double)test_simulator.GetParticleAt(0).position.x==Approx(197.6));
      REQUIRE((double)test_simulator.GetParticleAt(0).position.y==Approx(50.5));
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
    REQUIRE((double)test_simulator.GetParticleAt(0).velocity.x==Approx(-1.0));
    REQUIRE((double)test_simulator.GetParticleAt(0).velocity.y==Approx(-1.0));
    REQUIRE((double)test_simulator.GetParticleAt(1).velocity.x==Approx(1.0));
    REQUIRE((double)test_simulator.GetParticleAt(1).velocity.y==Approx(1.0));
  }

  SECTION("Particle colliding w/ another correctly change velocity") {
    Particle first_particle(vec2(50.0,50.0), vec2(1.0,1.0), 1, 1, "white");
    Particle second_particle(vec2(52.0,50.0), vec2(-1.0,-1.0), 1, 1, "white");

    test_simulator.ClearParticles(); //clear particle(s) from previous test(s)
    test_simulator.AddParticle(first_particle);
    test_simulator.AddParticle(second_particle);
    test_simulator.Update();

    //check velocities properly update
    REQUIRE((double)test_simulator.GetParticleAt(0).velocity.x==Approx(-1.0));
    REQUIRE((double)test_simulator.GetParticleAt(0).velocity.y==Approx(1.0));
    REQUIRE((double)test_simulator.GetParticleAt(1).velocity.x==Approx(1.0));
    REQUIRE((double)test_simulator.GetParticleAt(1).velocity.y==Approx(-1.0));
  }
}