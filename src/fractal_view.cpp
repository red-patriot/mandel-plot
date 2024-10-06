#include "fractal_view.hpp"

#include <format>
#include <iostream>
#include <stdexcept>

#include <random>
#include <limits>

namespace plot {
  std::unique_ptr<FractalView> FractalView::instance_{nullptr};

  FractalView* FractalView::init(plot::Canvas canvas) {
    if (instance_) {
      return nullptr;
    }

    instance_ = std::make_unique<FractalView>(std::move(canvas));
    return instance_.get();
  }

  FractalView::FractalView(plot::Canvas canvas) :
      canvas_(std::move(canvas)) {
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
                               canvas_.width(), canvas_.height(), 0);
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
    // For now, just show random colors
    // TODO: actually calculate colors here
    static int y = 0;
    static std::random_device rd;
    static std::mt19937 generator{rd()};
    static std::uniform_int_distribution<std::uint32_t> distribution{0u, std::numeric_limits<std::uint32_t>::max()};

    for (int x = 0; x != canvas_.width(); ++x) {
      canvas_(x, y) = distribution(generator) | plot::ALPHA_MASK;
    }

    ++y;
    y = y % canvas_.height();
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
                                             canvas_.getAllValues()),
                SDL_DestroyTexture};
    SDL_RenderCopy(renderer_, texture.get(), nullptr, nullptr);

    SDL_RenderPresent(renderer_);
  }
}  // namespace mandel
