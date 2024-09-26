#include "fractal_view.hpp"

#include <format>
#include <stdexcept>

namespace mandel {
  mandel::FractalView* FractalView::instance_{nullptr};

  FractalView* FractalView::init(int width, int height) {
    if (instance_) {
      return nullptr;
    }

    instance_ = new FractalView(width, height);
    return instance_;
  }

  FractalView::FractalView(int width, int height) :
      width_(width),
      height_(height) {
    if (auto errorCode = SDL_Init(SDL_INIT_VIDEO);
        errorCode != 0) {
      throw std::runtime_error(std::format("Failed to initialize SDL with error {}, {}",
                                           errorCode, SDL_GetError()));
    }
    if ((width <= 0 || height <= 0)) {
      throw std::invalid_argument("Window width and height must be greater than 0");
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

  void FractalView::render() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);

    // TODO: Display points

    SDL_RenderPresent(renderer_);
  }
}  // namespace mandel
