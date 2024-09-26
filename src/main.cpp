#include "fractal_view.hpp"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main() {
  auto view = mandel::FractalView::init(1600, 900);

  // TODO: do other work here
  std::this_thread::sleep_for(5s);

  return 0;
}
