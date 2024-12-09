#include "canvas.hpp"

#include <algorithm>
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
  Canvas::Canvas(const Canvas& other) :
      points_(SDL_CreateRGBSurface(0,
                                   other.width_, other.height_, 32,
                                   RED_MASK,
                                   GREEN_MASK,
                                   BLUE_MASK,
                                   ALPHA_MASK),
              SDL_FreeSurface),
      width_(other.width_),
      height_(other.height_),
      min_(other.min_),
      max_(other.max_) {
    std::copy(other.begin(), other.end(), this->begin());
  }

  Canvas& Canvas::operator=(const Canvas& other) {
    points_.reset(SDL_CreateRGBSurface(0,
                                       other.width_, other.height_, 32,
                                       RED_MASK,
                                       GREEN_MASK,
                                       BLUE_MASK,
                                       ALPHA_MASK));
    std::copy(other.begin(), other.end(), this->begin());
    width_ = other.width_;
    height_ = other.height_;
    min_ = other.min_;
    max_ = other.max_;

    return *this;
  }

  bool Canvas::finished() const {
    std::unique_lock lk{writeLock_};
    return std::none_of(begin(), end(),
                        [](const Color& c) {
                          return alpha(c) == 0;
                        });
  }

  Color& Canvas::operator[](const Point& location) {
    auto [x, y] = indexOf(location);
    return *colorAt(points_->pixels, x, y);
  }
  const Color& Canvas::operator[](const Point& location) const {
    auto [x, y] = indexOf(location);
    return *colorAt(points_->pixels, x, y);
  }

  Color& Canvas::operator()(size_t x, size_t y) {
    return *colorAt(points_->pixels, x, y);
  }
  const Color& Canvas::operator()(size_t x, size_t y) const {
    return *colorAt(points_->pixels, x, y);
  }

  Canvas::Point Canvas::valueOf(size_t x, size_t y) const {
    return Point{
        ((max_.real() - min_.real()) / width_) * x + min_.real(),
        ((max_.imag() - min_.imag()) / height_) * y + min_.imag()};
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

  Canvas::DrawableView Canvas::getDrawableView(SDL_Renderer* renderer) const {
    std::unique_lock lk{writeLock_};
    return DrawableView(SDL_CreateTextureFromSurface(renderer, points_.get()),
                        SDL_DestroyTexture);
  }

  std::span<Color> Canvas::row(size_t y) {
    return {
        colorAt(points_->pixels, 0, y),
        width()};
  }

  void Canvas::setRow(size_t y, std::span<Color> colors) {
    std::shared_lock lk{writeLock_};
    std::ranges::copy(colors, row(y).begin());
  }

  Color* Canvas::begin() {
    return uncheckedColorAt(points_->pixels, 0, 0);
  }
  Color* Canvas::end() {
    return uncheckedColorAt(points_->pixels, width(), height() - 1);
  }
  Color const* Canvas::begin() const {
    return uncheckedColorAt(points_->pixels, 0, 0);
  }
  Color const* Canvas::end() const {
    return uncheckedColorAt(points_->pixels, width(), height() - 1);
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

  Color* Canvas::colorAt(void* pixels, size_t x, size_t y) const {
    if (y * width_ + x >= width_ * height_) {
      throw std::invalid_argument(std::format("Point ({}, {}) is off the the canvas",
                                              x, y));
    }
    return uncheckedColorAt(pixels, x, y);
  }

  Color* Canvas::uncheckedColorAt(void* pixels, size_t x, size_t y) const {
    return reinterpret_cast<Color*>(pixels) + (y * width_ + x);
  }
}  // namespace plot
