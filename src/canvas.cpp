#include "canvas.hpp"

namespace plot {
  Canvas::Canvas(const Point& minPoint,
                 const Point& maxPoint,
                 size_t width, size_t height) :
      points_(height, width) { }

  Canvas::View Canvas::allPoints() const {
    return points_;
  }
}  // namespace plot
