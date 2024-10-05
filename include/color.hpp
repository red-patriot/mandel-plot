#ifndef MANDEL_PLOT_COLOR_HPP
#define MANDEL_PLOT_COLOR_HPP

#include <array>
#include <cstdint>

namespace plot {
  using Color = std::uint32_t;

  static constexpr Color RED_MASK = 0xFF'00'00'00;
  static constexpr Color GREEN_MASK = 0x00'FF'00'00;
  static constexpr Color BLUE_MASK = 0x00'00'FF'00;
  static constexpr Color ALPHA_MASK = 0x00'00'00'FF;

  static constexpr Color RED{RED_MASK | ALPHA_MASK};
  static constexpr Color GREEN{GREEN_MASK | ALPHA_MASK};
  static constexpr Color BLUE{BLUE_MASK | ALPHA_MASK};
  static constexpr Color BLACK{ALPHA_MASK};
  static constexpr Color WHITE{RED | GREEN | BLUE};

  Color combineColor(std::uint8_t red,
                     std::uint8_t green,
                     std::uint8_t blue,
                     std::uint8_t alpha);

  std::uint8_t red(Color color);
  std::uint8_t green(Color color);
  std::uint8_t blue(Color color);
  std::uint8_t alpha(Color color);
}  // namespace plot

#endif
