#ifndef MANDEL_PLOT_CANVAS_HPP
#define MANDEL_PLOT_CANVAS_HPP

#include <Eigen/Core>
#include <complex>
#include <memory>

#include <SDL2/SDL_surface.h>

#include "color.hpp"

namespace plot {
  class Canvas {
   public:
    using Point = std::complex<double>;
    using Plane = Eigen::Array<Color, Eigen::Dynamic, Eigen::Dynamic>;

    Canvas(const Point& minPoint,
           const Point& maxPoint,
           size_t width, size_t height);

    size_t width() const { return width_; }
    size_t height() const { return height_; }

    Color& operator[](const Point& location);
    const Color& operator[](const Point& location) const;
    Color& operator()(size_t row, size_t column);
    const Color& operator()(size_t row, size_t column) const;

    Point min() const { return min_; }
    Point max() const { return max_; }
    Point span() const;
    Point step() const;

   private:
    Plane points_;

    std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> points2_;
    size_t width_;
    size_t height_;

    Point min_;
    Point max_;

    std::pair<Eigen::Index, Eigen::Index> indexOf(const Point& location) const;
  };
}  // namespace plot

#endif
