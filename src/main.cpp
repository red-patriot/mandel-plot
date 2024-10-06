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

  auto view = plot::FractalView::init(std::move(canvas));

  view->showPlot();

  return 0;
}
