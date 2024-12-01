#ifndef MANDEL_PLOT_ARGUMENT_PARSE_HPP
#define MANDEL_PLOT_ARGUMENT_PARSE_HPP

#include <vector>

#include "color.hpp"

namespace plot {
  struct Options {
    Color inColor{plot::BLACK};
    std::vector<Color> palette{0x33'CE'FF'FF,
                               0x33'68'FF'FF,
                               0x64'33'FF'FF,
                               0xCA'33'FF'FF,
                               0xFF'33'CE'FF,
                               0xFF'33'68'FF};

    friend bool operator==(const Options&, const Options&) = default;
  };

  Options parse(int argc, char** argv);
}  // namespace plot

#endif
