#ifndef MANDEL_PLOT_FRACTAL_VIEW_HPP
#define MANDEL_PLOT_FRACTAL_VIEW_HPP

#include <memory>

#include <SDL2/SDL.h>

namespace mandel {
  class FractalView {
   public:
    static FractalView* init(int width, int height);
    ~FractalView();

    void render();

   private:

    static FractalView* instance_;

    int width_;
    int height_;
    SDL_Window* window_{nullptr};
    SDL_Renderer* renderer_{nullptr};

    FractalView(int width, int height);

    FractalView(const FractalView&) = delete;
    FractalView& operator=(const FractalView&) = delete;
    FractalView(FractalView&&) = delete;
    FractalView& operator=(FractalView&&) = delete;

  };
}  // namespace mandel

#endif
