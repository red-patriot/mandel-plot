
#include "argument_parse.hpp"
#include "canvas.hpp"
#include "fractal_view.hpp"
#include "mandelbrot.hpp"
#include "parallel_calculator.hpp"
#include "simple_calculator.hpp"

using namespace std::chrono_literals;
using std::operator""i;

int main(int argc, char** argv) {
  auto options = plot::parse(argc, argv);

  auto canvas = std::make_shared<plot::Canvas>(-2.5 + 1.5i,
                                               1.0 - 1.5i,
                                               1108, 950);
  std::unique_ptr<plot::ColorCalculator> calculator =
      std::make_unique<plot::ParallelCalculator>(options.workerCount,
                                                 options.palette,
                                                 options.inColor,
                                                 mandelbrot::escapeTime,
                                                 canvas);

  auto view = plot::FractalView::init(std::move(canvas),
                                      std::move(calculator));

  view->showPlot();

  return 0;
}
