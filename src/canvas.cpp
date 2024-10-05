#include "canvas.hpp"

namespace plot {
  Canvas::Canvas(const Point& minPoint,
                 const Point& maxPoint,
                 size_t width, size_t height) :
      points_(SDL_CreateRGBSurface(0,
                                   width, height, 32,
                                   RED_MASK,
                                   GREEN_MASK,
                                   BLUE_MASK,
                                   ALPHA_MASK),
              SDL_FreeSurface),
      width_(width),
      height_(height),
      min_(minPoint),
      max_(maxPoint) { }

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

  SDL_Surface* Canvas::getAllValues() const {
    return points_.get();
  }

  std::pair<size_t, size_t> Canvas::indexOf(const Point& location) const {
    size_t column = width() / (max_.real() - min_.real()) * (location.real() - min_.real());
    size_t row = height() / (max_.imag() - min_.imag()) * (location.imag() - min_.imag());

    return {column, row};
  }

  Color& Canvas::colorAt(void* pixels, size_t x, size_t y) {
    return reinterpret_cast<Color*>(pixels)[y * width_ + x];
  }

  const Color& Canvas::colorAt(void* pixels, size_t x, size_t y) const {
    return reinterpret_cast<Color*>(pixels)[y * width_ + x];
  }
}  // namespace plot
