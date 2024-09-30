#ifndef MANDEL_PLOT_CANVAS_HPP
#define MANDEL_PLOT_CANVAS_HPP

#include <complex>

#include <Eigen/Core>

namespace plot {
  class Canvas {
   public:
    using Point = std::complex<long double>;
    using Plane = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
    using View = const Plane&;

    Canvas(const Point& minPoint,
           const Point& maxPoint,
           size_t width, size_t height);

    View allPoints() const;

    size_t width() const { return points_.cols(); }
    size_t height() const { return points_.rows(); }

   private:
    Plane points_;
  };
}  // namespace plot

#endif
