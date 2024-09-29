#include "fractal_view.hpp"

#include <format>
#include <iostream>
#include <stdexcept>

namespace mandel {
  std::unique_ptr<FractalView> FractalView::instance_{nullptr};

  FractalView* FractalView::init(int width, int height) {
    if (instance_) {
      return nullptr;
    }

    instance_ = std::make_unique<FractalView>(width, height);
    return instance_.get();
  }

  FractalView::FractalView(int width, int height) :
      width_(width),
      height_(height) {
    if (instance_) {
      throw std::runtime_error("FractalView is already initialized");
    }
    if ((width <= 0 || height <= 0)) {
      throw std::invalid_argument("Window width and height must be greater than 0");
    }

    if (auto errorCode = SDL_Init(SDL_INIT_VIDEO);
        errorCode != 0) {
      throw std::runtime_error(std::format("Failed to initialize SDL with error {}, {}",
                                           errorCode, SDL_GetError()));
    }

    window_ = SDL_CreateWindow("Fractal",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               width_, height_, 0);
    if (!window_) {
      throw std::runtime_error(std::format("Failed to create a window with error {}",
                                           SDL_GetError()));
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
      throw std::runtime_error(std::format("Failed to create a renderer with error {}",
                                           SDL_GetError()));
    }
  }

  FractalView::~FractalView() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    SDL_Quit();
  }

  void FractalView::showPlot() {
    while (running_) {
      handleInput();
      updatePlot();
      generateOutput();
    }
  }

  void FractalView::handleInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          running_ = false;
          break;
        default:
          break;
      }
    }
  }
  void FractalView::updatePlot() {
    // TODO
  }
  void FractalView::generateOutput() {
    if (int error = SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
        error) {
      std::cerr << "SetRenderDrawColor failed with error " << SDL_GetError() << '\n';
      return;
    }
    if (int error = SDL_RenderClear(renderer_);
        error) {
      std::cerr << "RenderClear failed with error " << SDL_GetError() << '\n';
      return;
    }

    // TODO: Display points
    SDL_RenderPresent(renderer_);
  }
}  // namespace mandel