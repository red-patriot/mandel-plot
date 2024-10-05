#include "color.hpp"

static constexpr int RED_OFFSET = 24;
static constexpr int GREEN_OFFSET = 16;
static constexpr int BLUE_OFFSET = 8;

namespace plot {
  Color combineColor(std::uint8_t red,
                     std::uint8_t green,
                     std::uint8_t blue,
                     std::uint8_t alpha) {
    return (static_cast<std::uint32_t>(red) << RED_OFFSET) |
           (static_cast<std::uint32_t>(green) << GREEN_OFFSET) |
           (static_cast<std::uint32_t>(blue) << BLUE_OFFSET) |
           static_cast<std::uint32_t>(alpha);
  }

  std::uint8_t red(Color color) {
    return (color & RED_MASK) >> RED_OFFSET;
  }
  std::uint8_t green(Color color) {
    return (color & GREEN_MASK) >> GREEN_OFFSET;
  }
  std::uint8_t blue(Color color) {
    return (color & BLUE_MASK) >> BLUE_OFFSET;
  }
  std::uint8_t alpha(Color color) {
    return color & ALPHA_MASK;
  }
}  // namespace plot
