#include "fractal_view.hpp"

#include <format>
#include <iostream>
#include <stdexcept>

#include <random>
#include <limits>

namespace plot {
  std::unique_ptr<FractalView> FractalView::instance_{nullptr};

  FractalView* FractalView::init(std::shared_ptr<plot::Canvas> canvas,
                                 plot::ColorCalculator calculator) {
    if (instance_) {
      return nullptr;
    }

    instance_ = std::make_unique<FractalView>(std::move(canvas), calculator);
    return instance_.get();
  }

  FractalView::FractalView(std::shared_ptr<plot::Canvas> canvas,
                           plot::ColorCalculator calculator) :
      canvas_(std::move(canvas)),
      calculator_(std::move(calculator)) {
    if (instance_) {
      throw std::runtime_error("FractalView is already initialized");
    }

    if (auto errorCode = SDL_Init(SDL_INIT_VIDEO);
        errorCode != 0) {
      throw std::runtime_error(std::format("Failed to initialize SDL with error {}, {}",
                                           errorCode, SDL_GetError()));
    }

    window_ = SDL_CreateWindow("Fractal",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               canvas_->width(), canvas_->height(), 0);
    if (!window_) {
      throw std::runtime_error(std::format("Failed to create a window with error {}",
                                           SDL_GetError()));
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
      throw std::runtime_error(std::format("Failed to create a renderer with error {}",
                                           SDL_GetError()));
    }

    drawStart_ = std::chrono::steady_clock::now();
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
    if (calculator_.finished()) {
      return;
    }

    calculator_.update();
    if (calculator_.finished()) {
      auto drawDone = std::chrono::steady_clock::now();
      auto drawTime = drawDone - drawStart_;
      std::cout << std::string(80, '*') << '\n'
                << std::format("\tDrawing took {:%S} s", drawTime) << '\n';
    }
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

    std::unique_ptr<SDL_Texture,
                    void (*)(SDL_Texture*)>
        texture{SDL_CreateTextureFromSurface(renderer_,
                                             canvas_->getAllValues()),
                SDL_DestroyTexture};
    SDL_RenderCopy(renderer_, texture.get(), nullptr, nullptr);

    SDL_RenderPresent(renderer_);
  }
}  // namespace plot
