#ifndef MANDEL_PLOT_CANVAS_HPP
#define MANDEL_PLOT_CANVAS_HPP

#include <Eigen/Core>

namespace plot {
  class Canvas {
   public:
    using Points = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
    using View = const Points&;

    Canvas(const Eigen::Vector2d& minPoint,
           const Eigen::Vector2d& maxPoint,
           size_t width, size_t height);

    View getPoints() const;

    size_t width() const { return points_.cols(); }
    size_t height() const { return points_.rows(); }

   private:
    Points points_;
  };
}  // namespace plot

#endif
