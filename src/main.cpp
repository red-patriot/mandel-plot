#include <chrono>
#include <limits>
#include <memory>
#include <thread>

#include "canvas.hpp"
#include "fractal_view.hpp"
#include "mandelbrot.hpp"

using namespace std::chrono_literals;
using std::operator""i;

int main() {
  auto canvas = std::make_shared<plot::Canvas>(-2.5 + 1.75i,
                                               1.0 - 1.75i,
                                               1000, 1000);
  plot::ColorCalculator calculator({0x33CEFFFF,
                                    0x3368FFFF,
                                    0x6433FFFF,
                                    0xCA33FFFF,
                                    0xFF33CEFF,
                                    0xFF3368FF},
                                   mandelbrot::escapeTime,
    canvas);

  auto view = plot::FractalView::init(std::move(canvas),
                                      std::move(calculator));

  view->showPlot();

  return 0;
}
