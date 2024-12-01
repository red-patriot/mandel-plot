#include <gtest/gtest.h>

#include <vector>
#include <string>

#include "argument_parse.hpp"

struct Args {
  int argc;
  std::vector<char*> argv;
};

/** Helper to get raw argument values from a nicer interface */
static Args makeRawArgs(const std::vector<std::string>& values) {
  int argc = values.size();
  std::vector<char*> argv;
  argv.reserve(argc);
  for (const auto& str : values) {
    // This is probably a REALLY bad thing to do, but it is fine for JUST the tests below...
    argv.push_back(const_cast<char*>(str.c_str()));
  }

  return {argc, argv};
}

TEST(TestArguments, ParsesDefaults) {
  std::vector<std::string> args{"/dummy/program/path"};
  auto [argc, argv] = makeRawArgs(args);

  plot::Options expected{
      .inColor = plot::BLACK,
      .palette = {
          0x33'CE'FF'FF, 0x33'68'FF'FF, 0x64'33'FF'FF, 0xCA'33'FF'FF, 0xFF'33'CE'FF, 0xFF'33'68'FF}};

  auto actual = plot::parse(argc, argv.data());

  EXPECT_EQ(expected, actual);
}

TEST(TestArguments, ParseInColor) {
  std::vector<std::string> args{
      "/dummy/program/path",
      "-c",
      "0xFFFFFFFF"};
  auto [argc, argv] = makeRawArgs(args);

  plot::Options expected{
      .inColor = plot::WHITE,
      .palette = {0x33'CE'FF'FF,
                  0x33'68'FF'FF,
                  0x64'33'FF'FF,
                  0xCA'33'FF'FF,
                  0xFF'33'CE'FF,
                  0xFF'33'68'FF}};

  auto actual = plot::parse(argc, argv.data());

  EXPECT_EQ(expected, actual);
}

TEST(TestArguments, ParsePalette) {
  std::vector<std::string> args{
      "/dummy/program/path",
      "-p",
      "0xFF0000FF",
      "0x00FF00FF",
      "0x0000FFFF"};
  auto [argc, argv] = makeRawArgs(args);

  plot::Options expected{
      .inColor = plot::BLACK,
      .palette = {0xFF'00'00'FF,
                  0x00'FF'00'FF,
                  0x00'00'FF'FF}};

  auto actual = plot::parse(argc, argv.data());

  EXPECT_EQ(expected, actual);
}
