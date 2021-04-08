#include "visualizer/ideal_gas_simulator.h"
#include "core/particle.h"
#include "cinder/gl/gl.h"
#include <catch2/catch.hpp>
#include <vector>

using glm::vec2;
using idealgas::visualizer::IdealGasSimulator;
using idealgas::ParticleGroup;
using idealgas::Particle;
using std::vector;

//set up particle group for testing
vector<ParticleGroup*> test_groups;
ParticleGroup* first_group = new ParticleGroup(0,1,1,"white",100.0,100.0,2.0);

bool AreVelocitiesEqual(const vec2& first, const vec2& second) {
  return (double) first.x == Approx((double) second.x).epsilon(0.1) &&
         (double) first.y == Approx((double) second.y).epsilon(0.1);
}

TEST_CASE("Particles collisions handled correctly by simulator") {
  test_groups.push_back(first_group);
  Particle test_particle(vec2(50.0,50.0), vec2(1.0,1.0), 1, 1, "white");

  SECTION("Collisions between same type particles handled correctly") {
    SECTION("Particles moving away from each other do not collide") {
      IdealGasSimulator test_simulator(vec2(0,0),test_groups,500.0,500.0,100.0,
                                       100.0,50.0,10,2);
      Particle same_non_colliding_particle(vec2(48.0,50.0), vec2(-1.0,-1.0),
                                                1, 1, "white");
      first_group->AddParticle(test_particle);
      first_group->AddParticle(same_non_colliding_particle);
      test_simulator.Update();

      //check velocities do NOT change
      REQUIRE(AreVelocitiesEqual(first_group->GetParticleAt(0)->velocity,
                            vec2(1.0,1.0)));
      REQUIRE(AreVelocitiesEqual(first_group->GetParticleAt(1)->velocity,
                            vec2(-1.0,-1.0)));
    }

    SECTION("Particles colliding correctly change velocity") {
      IdealGasSimulator test_simulator(vec2(0,0),test_groups,500.0,500.0,100.0,
                                       100.0,50.0,10,2);
      Particle same_colliding_particle(vec2(52.0,50.0), vec2(-1.0,-1.0), 1, 1, "white");
      first_group->ClearParticles();
      first_group->AddParticle(test_particle);
      first_group->AddParticle(same_colliding_particle);
      test_simulator.Update();

      //check velocities update correctly
      REQUIRE(AreVelocitiesEqual(first_group->GetParticleAt(0)->velocity,
                            vec2(-1.0,1.0)));
      REQUIRE(AreVelocitiesEqual(first_group->GetParticleAt(1)->velocity,
                            vec2(1.0,-1.0)));
    }

    SECTION("Pairs of particles collide correctly with >2 particles in box") {
      IdealGasSimulator test_simulator(vec2(0,0),test_groups,500.0,500.0,100.0,
                                       100.0,50.0,10,2);
      Particle extra_particle(vec2(30.0,30.0), vec2(0.5,1.5), 1, 1, "white");
      first_group->AddParticle(extra_particle);
      test_simulator.Update();

      //check only colliding particle velocities update
      REQUIRE(AreVelocitiesEqual(first_group->GetParticleAt(0)->velocity,
                                 vec2(-1.0,1.0)));
      REQUIRE(AreVelocitiesEqual(first_group->GetParticleAt(1)->velocity,
                                 vec2(1.0,-1.0)));
      REQUIRE(AreVelocitiesEqual(first_group->GetParticleAt(2)->velocity,
                                 vec2(0.5,1.5)));
    }
  }

  SECTION("Collisions between different type particles handled correctly") {
    ParticleGroup* second_group = new ParticleGroup(0,2,2,"red",100.0,100.0,2.0);
    test_groups.push_back(second_group);

    SECTION("Different particles moving away from each other don't collide") {
      IdealGasSimulator test_simulator(vec2(0,0),test_groups,500.0,500.0,100.0,
                                       100.0,50.0,10,2);
      Particle different_non_colliding_particle(vec2(47.0,50.0),vec2(-1.0,-1.0),
                                                2, 2, "red");
      first_group->ClearParticles();
      first_group->AddParticle(test_particle);
      second_group->AddParticle(different_non_colliding_particle);
      test_simulator.Update();

      //check velocities do NOT change
      REQUIRE(AreVelocitiesEqual(first_group->GetParticleAt(0)->velocity,
                              vec2(1.0,1.0)));
      REQUIRE(AreVelocitiesEqual(second_group->GetParticleAt(0)->velocity,
                              vec2(-1.0,-1.0)));
    }

    SECTION("Different particles update correctly after colliding") {
      IdealGasSimulator test_simulator(vec2(0,0),test_groups,500.0,500.0,100.0,
                                       100.0,50.0,10,2);
      Particle different_colliding_particle(vec2(53.0,50.0),vec2(-1.0,-1.0),
                                                2, 2, "red");
      first_group->ClearParticles();
      first_group->AddParticle(test_particle);
      second_group->ClearParticles();
      second_group->AddParticle(different_colliding_particle);
      test_simulator.Update();

      //check velocities update correctly
      REQUIRE(AreVelocitiesEqual(first_group->GetParticleAt(0)->velocity,
                              vec2(-1.67,1.0)));
      REQUIRE(AreVelocitiesEqual(second_group->GetParticleAt(0)->velocity,
                              vec2(0.33,-1.0)));
    }

    ParticleGroup* third_group = new ParticleGroup(0,5,3,"green",100.0,100.0,2.0);
    test_groups.push_back(third_group);

    SECTION("Different particles collide properly w/ multiple different groups") {
      IdealGasSimulator test_simulator(vec2(0,0),test_groups,500.0,500.0,100.0,
                                       100.0,50.0,10,2);
      Particle different_colliding_particle(vec2(53.0,50.0),vec2(-1.0,-1.0),2,2,"red");
      Particle extra_particle(vec2(4.0,5.0),vec2(-1.0,-1.0),5, 3, "green");
      first_group->ClearParticles();
      first_group->AddParticle(test_particle);
      second_group->AddParticle(different_colliding_particle);
      third_group->AddParticle(extra_particle);
      test_simulator.Update();

      //check only colliding particle velocities update
      REQUIRE(AreVelocitiesEqual(first_group->GetParticleAt(0)->velocity,
                              vec2(-1.67,1.0)));
      REQUIRE(AreVelocitiesEqual(second_group->GetParticleAt(0)->velocity,
                              vec2(0.33,-1.0)));
      REQUIRE(AreVelocitiesEqual(third_group->GetParticleAt(0)->velocity,
                              vec2(-1.0,-1.0)));
    }
  }
}