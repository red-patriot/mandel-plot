#ifndef MANDEL_PLOT_CANVAS_HPP
#define MANDEL_PLOT_CANVAS_HPP

#include <Eigen/Core>
#include <complex>

#include "color.hpp"

namespace plot {
  class Canvas {
   public:
    using Point = std::complex<double>;
    using Plane = Eigen::Array<Color, Eigen::Dynamic, Eigen::Dynamic>;
    using View = const Plane&;

    Canvas(const Point& minPoint,
           const Point& maxPoint,
           size_t width, size_t height);

    View allPoints() const;

    size_t width() const { return points_.cols(); }
    size_t height() const { return points_.rows(); }

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

    Point min_;
    Point max_;

    std::pair<Eigen::Index, Eigen::Index> indexOf(const Point& location) const;
  };
}  // namespace plot

#endif
