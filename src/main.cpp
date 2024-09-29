#include "fractal_view.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main() {
  auto view = mandel::FractalView::init(1600, 900);

  view->showPlot();

  return 0;
}
