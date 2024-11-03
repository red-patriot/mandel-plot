#include "simple_calculator.hpp"

#include <cmath>
#include <cassert>
#include <algorithm>

#include "escape_constants.hpp"

using std::operator""i;

namespace plot {
  void SimpleCalculator::update() {
    if (finished()) {
      return;
    }

    // calculate 1 row of the plot at a time
    auto currentRow = getCanvas().row(currentRow_);
    for (currentCol_ = 0; currentCol_ != getCanvas().width(); ++currentCol_) {
      auto point = getCanvas().valueOf(currentCol_, currentRow_);
      auto color = findColor(point);
      currentRow[currentCol_] = color;
    }
    auto reflectedRow = getCanvas().row(getCanvas().height() - (currentRow_ + 1));
    std::ranges::copy(currentRow, reflectedRow.begin());

    logPoints(getCanvas().width() * 2);

    ++currentRow_;
  }

}  // namespace plot
