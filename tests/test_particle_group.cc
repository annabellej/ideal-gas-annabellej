#include <catch2/catch.hpp>
#include "core/particle_group.h"
#include "cinder/gl/gl.h"

using idealgas::Particle;
using idealgas::ParticleGroup;
using glm::vec2;

ParticleGroup* test_group = new ParticleGroup(2, 1, 1, "white", 100.0,100.0,1.0);

bool AreVectorsEqual(vec2 first, vec2 second) {
  return (double) first.x == Approx((double) second.x) &&
         (double) first.y == Approx((double) second.y);
}

TEST_CASE("Group of particles properly constructed based on given arguments") {
  SECTION("Initial particle velocity for group is w/in limit") {
    REQUIRE((test_group->GetParticleAt(0)->velocity.x < 1.0 &&
            test_group->GetParticleAt(0)->velocity.y < 1.0));
  }

  SECTION("Particle positions are w/in limits") {
    REQUIRE((test_group->GetParticleAt(0)->position.x < 100.0 &&
            test_group->GetParticleAt(0)->position.y < 100.0));

    REQUIRE((test_group->GetParticleAt(1)->position.x < 100.0 &&
            test_group->GetParticleAt(1)->position.y < 100.0));
  }
}

TEST_CASE("ParticleGroup updates all positions correctly based on velocities") {
  Particle test_particle(vec2(50.0,50.0), vec2(0.4,0.5), 1, 1, "white");
  Particle no_velocity_particle(vec2(20.0,20.0), vec2(0.0,0.0), 1, 1, "white");

  test_group->ClearParticles(); //clear particle(s) from previous test(s)
  test_group->AddParticle(test_particle);
  test_group->AddParticle(no_velocity_particle);
  test_group->UpdatePositions();

  SECTION("Particles update positions correctly based on velocities") {
    REQUIRE(AreVectorsEqual(test_group->GetParticleAt(0)->position,
                            vec2(50.4,50.5)));
  }

  SECTION("Particle(s) w/ 0,0 velocity do not move") {
    REQUIRE(AreVectorsEqual(test_group->GetParticleAt(1)->position,
                            vec2(20.0,20.0)));
  }
}

TEST_CASE("Particles colliding into walls update velocities appropriately") {
  SECTION("Touching top wall") {
    SECTION("Moving away from wall does not collide") {
      Particle test_particle(vec2(50.0,0.0), vec2(0.4,0.5), 1, 1, "white");
      test_group->ClearParticles(); //clear particle(s) from previous test(s)
      test_group->AddParticle(test_particle);
      test_group->HandlePossibleWallCollisions();

      //check velocity does NOT change
      REQUIRE(AreVectorsEqual(test_group->GetParticleAt(0)->velocity,
                              vec2(0.4,0.5)));
    }

    SECTION("Colliding w/ wall negates y component of velocity") {
      Particle test_particle(vec2(50.0,0.0), vec2(0.4,-0.5), 1, 1, "white");
      test_group->ClearParticles(); //clear particle(s) from previous test(s)
      test_group->AddParticle(test_particle);
      test_group->HandlePossibleWallCollisions();

      //check velocity properly updates
      REQUIRE(AreVectorsEqual(test_group->GetParticleAt(0)->velocity,
                             vec2(0.4,0.5)));
    }
  }

  SECTION("Touching bottom wall") {
    SECTION("Moving away from wall does not collide") {
      Particle test_particle(vec2(50.0,198.0), vec2(0.4,-0.5), 1, 1, "white");
      test_group->ClearParticles(); //clear particle(s) from previous test(s)
      test_group->AddParticle(test_particle);
      test_group->HandlePossibleWallCollisions();

      //check velocity does NOT change
      REQUIRE(AreVectorsEqual(test_group->GetParticleAt(0)->velocity,
                              vec2(0.4,-0.5)));
    }

    SECTION("Colliding w/ wall negates y component of velocity") {
      Particle test_particle(vec2(50.0,198.0), vec2(0.4,0.5), 1, 1, "white");
      test_group->ClearParticles(); //clear particle(s) from previous test(s)
      test_group->AddParticle(test_particle);
      test_group->HandlePossibleWallCollisions();

      //check velocity properly updates
      REQUIRE(AreVectorsEqual(test_group->GetParticleAt(0)->velocity,
                              vec2(0.4,-0.5)));
    }
  }

  SECTION("Touching left wall") {
    SECTION("Moving away from wall does not collide") {
      Particle test_particle(vec2(0.0,50.0), vec2(0.4,0.5), 1, 1, "white");
      test_group->ClearParticles(); //clear particle(s) from previous test(s)
      test_group->AddParticle(test_particle);
      test_group->HandlePossibleWallCollisions();

      //check velocity does NOT change
      REQUIRE(AreVectorsEqual(test_group->GetParticleAt(0)->velocity,
                              vec2(0.4,0.5)));
    }

    SECTION("Colliding w/ wall negates x component of velocity") {
      Particle test_particle(vec2(0.0,50.0), vec2(-0.4,0.5), 1, 1, "white");
      test_group->ClearParticles(); //clear particle(s) from previous test(s)
      test_group->AddParticle(test_particle);
      test_group->HandlePossibleWallCollisions();

      //check velocity properly updates
      REQUIRE(AreVectorsEqual(test_group->GetParticleAt(0)->velocity,
                              vec2(0.4,0.5)));
    }
  }

  SECTION("Touching right wall") {
    SECTION("Moving away from wall does not collide") {
      Particle test_particle(vec2(198.0,50.0), vec2(-0.4,0.5), 1, 1, "white");
      test_group->ClearParticles(); //clear particle(s) from previous test(s)
      test_group->AddParticle(test_particle);
      test_group->HandlePossibleWallCollisions();

      //check velocity does NOT change
      REQUIRE(AreVectorsEqual(test_group->GetParticleAt(0)->velocity,
                              vec2(-0.4,0.5)));
    }

    SECTION("Colliding w/ wall negates x component of velocity") {
      Particle test_particle(vec2(198.0,50.0), vec2(0.4,0.5), 1, 1, "white");
      test_group->ClearParticles(); //clear particle(s) from previous test(s)
      test_group->AddParticle(test_particle);
      test_group->HandlePossibleWallCollisions();

      //check velocity properly updates
      REQUIRE(AreVectorsEqual(test_group->GetParticleAt(0)->velocity,
                              vec2(-0.4,0.5)));
    }
  }
}