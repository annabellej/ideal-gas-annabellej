#include "core/particle_utils.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace particleutils {

double GenerateRandomDouble(double max_value, double min_value) {
  return (max_value - min_value) * (double) rand() / (double) RAND_MAX;
}

} // namespace particleutils

} // namespace idealgas