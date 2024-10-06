#ifndef MANDEL_PLOT_CANVAS_HPP
#define MANDEL_PLOT_CANVAS_HPP

#include <complex>
#include <memory>

#include <SDL2/SDL_surface.h>

#include "color.hpp"

namespace plot {
  class Canvas {
   public:
    using Point = std::complex<double>;

    Canvas(const Point& minPoint,
           const Point& maxPoint,
           int width, int height);

    int width() const { return width_; }
    int height() const { return height_; }

    Color& operator[](const Point& location);
    const Color& operator[](const Point& location) const;
    Color& operator()(size_t x, size_t y);
    const Color& operator()(size_t x, size_t y) const;

    Point min() const { return min_; }
    Point max() const { return max_; }
    Point span() const;
    Point step() const;

    SDL_Surface* getAllValues() const;

   private:
    std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> points_;
    int width_;
    int height_;

    Point min_;
    Point max_;

    std::pair<size_t, size_t> indexOf(const Point& location) const;
    Color& colorAt(void* pixels, size_t x, size_t y);
    const Color& colorAt(void* pixels, size_t x, size_t y) const;
  };
}  // namespace plot

#endif
