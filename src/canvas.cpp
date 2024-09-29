#include "canvas.hpp"

namespace plot {
  Canvas::Canvas(const Eigen::Vector2d& minPoint,
                 const Eigen::Vector2d& maxPoint,
                 size_t width, size_t height) :
      points_(height, width) { }

  Canvas::View Canvas::getPoints() const {
    return points_;
  }
}  // namespace plot
