#include "color.hpp"

namespace plot {
  Color::Color(std::uint8_t red,
               std::uint8_t green,
               std::uint8_t blue,
               std::uint8_t alpha) :
      color_{red, green, blue, alpha} { }
}  // namespace plot
