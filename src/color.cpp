#include "color.hpp"

namespace plot {
  Color::Color(std::uint8_t red,
               std::uint8_t green,
               std::uint8_t blue,
               std::uint8_t alpha) :
      color_{red, green, blue, alpha} { }

  Color::Color(std::uint32_t raw) :
      Color((raw & RED_MASK) >> 24,
            (raw & GREEN_MASK) >> 16,
            (raw & BLUE_MASK) >> 8,
            raw & ALPHA_MASK) {  }
}  // namespace plot
