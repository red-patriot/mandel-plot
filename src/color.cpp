#include "color.hpp"

#include <algorithm>

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

  Color interpolate(Color first,
                    Color second,
                    double ratio) {
    ratio = std::clamp(ratio, 0.0, 1.0);

    auto r1 = red(first);
    auto r2 = red(second);
    auto g1 = green(first);
    auto g2 = green(second);
    auto b1 = blue(first);
    auto b2 = blue(second);
    auto a1 = alpha(first);
    auto a2 = alpha(second);

    auto r = static_cast<std::uint8_t>(r1 * (1.0 - ratio) + r2 * ratio);
    auto g = static_cast<std::uint8_t>(g1 * (1.0 - ratio) + g2 * ratio);
    auto b = static_cast<std::uint8_t>(b1 * (1.0 - ratio) + b2 * ratio);
    auto a = static_cast<std::uint8_t>(a1 * (1.0 - ratio) + a2 * ratio);

    return combineColor(r, g, b, a);
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
