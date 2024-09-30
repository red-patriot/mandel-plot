#ifndef MANDEL_PLOT_COLOR_HPP
#define MANDEL_PLOT_COLOR_HPP

#include <cstdint>

namespace plot {
  struct Color {
    friend bool operator==(const Color&, const Color&) = default;

    std::uint8_t red;
    std::uint8_t green;
    std::uint8_t blue;
    std::uint8_t alpha;
  };

  namespace colors {
    static constexpr Color RED{255, 0, 0, 255};
    static constexpr Color GREEN{0, 255, 0, 255};
    static constexpr Color BLUE{0, 0, 255, 255};
    static constexpr Color BLACK{0, 0, 0, 255};
    static constexpr Color WHITE{255, 255, 255, 255};
  }  // namespace colors
}

#endif