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
  auto canvas = std::make_shared<plot::Canvas>(-2.5 + 1.5i,
                                               1.0 - 1.5i,
                                               1108, 950);
  plot::ColorCalculator calculator({0x33'CE'FF'FF,
                                    0x33'68'FF'FF,
                                    0x64'33'FF'FF,
                                    0xCA'33'FF'FF,
                                    0xFF'33'CE'FF,
                                    0xFF'33'68'FF},
                                   mandelbrot::escapeTime,
                                   canvas);

  auto view = plot::FractalView::init(std::move(canvas),
                                      std::move(calculator));

  view->showPlot();

  return 0;
}
