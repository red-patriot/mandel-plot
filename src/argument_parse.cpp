#include "argument_parse.hpp"

#include <iostream>

#include <argparse/argparse.hpp>

namespace plot {
  Options parse(int argc, char** argv) {
    argparse::ArgumentParser program{"mandel_plot"};
    std::vector<int> palette;

    program.add_argument("-c")
        .scan<'i', plot::Color>()
        .nargs(1)
        .help("The color to use for points in the set")
        .default_value(plot::BLACK);
    program.add_argument("-p")
        .help("The color palette to use for points outside the set")
        .scan<'i', plot::Color>()
        .nargs(argparse::nargs_pattern::at_least_one)
        .default_value<std::vector<Color>>({0x33'CE'FF'FF,
                                            0x33'68'FF'FF,
                                            0x64'33'FF'FF,
                                            0xCA'33'FF'FF,
                                            0xFF'33'CE'FF,
                                            0xFF'33'68'FF});

    program.parse_args(argc, argv);

    Options results{.inColor = program.get<Color>("-c"),
                    .palette = program.get<std::vector<Color>>("-p")};

    return results;
  }
}  // namespace plot
