#ifndef MANDEL_PLOT_FRACTAL_VIEW_HPP
#define MANDEL_PLOT_FRACTAL_VIEW_HPP

#include <memory>

#include <SDL2/SDL.h>

#include "canvas.hpp"

namespace mandel {
  /** A view window for an iterative Fractal */
  class FractalView {
   public:
    explicit FractalView(plot::Canvas canvas);
    ~FractalView();

    /**
     * Initializes a FractalView.
     *
     * \param width The witdh of the viewport to display
     * \param height The height of the viewport to display
     *
     * \throw std::runtime_error if there is already an instance created (there can only be one allowed at a time)
     */
    static FractalView* init(plot::Canvas canvas);

    /** Shows the plot */
    void showPlot();

   private:
    static std::unique_ptr<FractalView> instance_; /**< The unique view instance */

    plot::Canvas canvas_;
    int width_;                       /**< The width of the viewport. */
    int height_;                      /**< The height of the viewport. */
    SDL_Window* window_{nullptr};     /**< The SDL window to draw to. */
    SDL_Renderer* renderer_{nullptr}; /**< The Renderer to use to display the window contents. */
    bool running_{true};              /**< Indicates the main loop is still running. */

    FractalView(const FractalView&) = delete;
    FractalView& operator=(const FractalView&) = delete;
    FractalView(FractalView&&) = delete;
    FractalView& operator=(FractalView&&) = delete;

    /** Respond user input */
    void handleInput();
    /** Update the world */
    void updatePlot();
    /** Draw the output */
    void generateOutput();
  };
}  // namespace mandel

#endif
