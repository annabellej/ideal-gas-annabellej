#include "simulator.h"

namespace idealgas {

namespace visualizer {

using glm::vec2;

void Simulator::Draw() const {
  //draw rectangular container for particles
  vec2 pixel_bottom_right = top_left_corner_ +
                            vec2(container_width_, container_height_);

  ci::Rectf container_box(top_left_corner_, pixel_bottom_right);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(container_box);

  //TODO: draw particles

}

} // namespace visualizer

} // namespace idealgas