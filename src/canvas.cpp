#include "canvas.hpp"

#include <format>
#include <stdexcept>

namespace plot {
  Canvas::Canvas(const Point& firstPoint,
                 const Point& secondPoint,
                 int width, int height) :
      points_(SDL_CreateRGBSurface(0,
                                   width, height, 32,
                                   RED_MASK,
                                   GREEN_MASK,
                                   BLUE_MASK,
                                   ALPHA_MASK),
              SDL_FreeSurface),
      width_(width),
      height_(height),
      min_(calculateMin(firstPoint, secondPoint)),
      max_(calculateMax(firstPoint, secondPoint)) {
    if (width <= 0) {
      throw std::invalid_argument("Width must be greater than 0");
    }
    if (height <= 0) {
      throw std::invalid_argument("Height must be greater than 0");
    }
  }

  Color& Canvas::operator[](const Point& location) {
    auto [x, y] = indexOf(location);
    return colorAt(points_->pixels, x, y);
  }
  const Color& Canvas::operator[](const Point& location) const {
    auto [x, y] = indexOf(location);
    return colorAt(points_->pixels, x, y);
  }

  Color& Canvas::operator()(size_t x, size_t y) {
    return colorAt(points_->pixels, x, y);
  }
  const Color& Canvas::operator()(size_t x, size_t y) const {
    return colorAt(points_->pixels, x, y);
  }

  Canvas::Point Canvas::span() const {
    return max_ - min_;
  }

  Canvas::Point Canvas::step() const {
    return {span().real() / width(),
            span().imag() / height()};
  }

  Canvas::View Canvas::getAllValues() const {
    return points_.get();
  }

  Canvas::Point Canvas::calculateMin(Canvas::Point first, Canvas::Point second) {
    return Point{std::min(first.real(), second.real()),
                 std::min(first.imag(), second.imag())};
  }
  Canvas::Point Canvas::calculateMax(Canvas::Point first, Canvas::Point second) {
    return Point{std::max(first.real(), second.real()),
                 std::max(first.imag(), second.imag())};
  }

  std::pair<size_t, size_t> Canvas::indexOf(const Point& location) const {
    size_t column = static_cast<size_t>(width() / (max_.real() - min_.real()) * (location.real() - min_.real()));
    size_t row = static_cast<size_t>(height() / (max_.imag() - min_.imag()) * (location.imag() - min_.imag()));

    return {column, row};
  }

  Color& Canvas::colorAt(void* pixels, size_t x, size_t y) {
    if (y * width_ + x >= width_ * height_) {
      throw std::invalid_argument(std::format("Point ({}, {}) is off the the canvas",
                                              x, y));
    }
    return reinterpret_cast<Color*>(pixels)[y * width_ + x];
  }

  const Color& Canvas::colorAt(void* pixels, size_t x, size_t y) const {
    if (y * width_ + x >= width_ * height_) {
      throw std::invalid_argument(std::format("Point ({}, {}) is off the the canvas",
                                              x, y));
    }
    return reinterpret_cast<Color*>(pixels)[y * width_ + x];
  }
}  // namespace plot
