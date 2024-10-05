#include <chrono>
#include <limits>
#include <thread>

#include "canvas.hpp"
#include "fractal_view.hpp"

using namespace std::chrono_literals;
using std::operator""i;

int main() {
  plot::Canvas canvas{-1.0 - 1.0i,
                      1.0 + 1.0i,
                      1024, 512};

  // For now, just use some hardcoded colors to see the canvas being rendered
  for (int i = 0; i < canvas.height(); ++i) {
    for (int j = 0; j < canvas.width(); ++j) {
      canvas(i, j) = plot::Color{(std::uint8_t)i,
                                 0,
                                 (std::uint8_t)j,
                                 255};
    }
  }

  auto view = mandel::FractalView::init(std::move(canvas));

  view->showPlot();

  return 0;
}
