#include "core/particle.h"

namespace idealgas {

bool operator<(const Particle& lhs, const Particle& rhs) {
  if (lhs.mass == rhs.mass) {
    return lhs.radius < rhs.radius;
  } else {
    return lhs.mass < rhs.mass;
  }
}

} // namespace idealgas