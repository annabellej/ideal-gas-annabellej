#pragma once

namespace idealgas {

namespace particleutils {

/**
 * Generates a random double between a given min and max value.
 *
 * @param   max_value the max value to generate.
 * @param   min_value the min value to generate.
 *
 * @return  a random double in the given range.
 */
double GenerateRandomDouble(double max_value, double min_value);

} // namespace particleutils

} // namespace idealgas