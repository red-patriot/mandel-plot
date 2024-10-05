#ifndef MANDEL_PLOT_COLOR_HPP
#define MANDEL_PLOT_COLOR_HPP

#include <array>
#include <cstdint>

namespace plot {
  class Color {
    friend bool operator==(const Color&, const Color&) = default;

   public:
    Color() = default;
    Color(std::uint8_t red,
          std::uint8_t green,
          std::uint8_t blue,
          std::uint8_t alpha);
    explicit Color(std::uint32_t raw);

    std::uint8_t red() const { return color_[0]; }
    std::uint8_t& red() { return color_[0]; }
    std::uint8_t green() const { return color_[1]; }
    std::uint8_t& green() { return color_[1]; }
    std::uint8_t blue() const { return color_[2]; }
    std::uint8_t& blue() { return color_[2]; }
    std::uint8_t alpha() const { return color_[3]; }
    std::uint8_t& alpha() { return color_[3]; }

    static constexpr std::uint32_t RED_MASK = 0xFF'00'00'00;
    static constexpr std::uint32_t GREEN_MASK = 0x00'FF'00'00;
    static constexpr std::uint32_t BLUE_MASK = 0x00'00'FF'00;
    static constexpr std::uint32_t ALPHA_MASK = 0x00'00'00'FF;

   private:
    std::array<uint8_t, 4> color_;
  };

  namespace colors {
    static const Color RED{255, 0, 0, 255};
    static const Color GREEN{0, 255, 0, 255};
    static const Color BLUE{0, 0, 255, 255};
    static const Color BLACK{0, 0, 0, 255};
    static const Color WHITE{255, 255, 255, 255};
  }  // namespace colors
}  // namespace plot

#endif
