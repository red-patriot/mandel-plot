#ifndef MANDEL_PLOT_CANVAS_HPP
#define MANDEL_PLOT_CANVAS_HPP

#include <complex>
#include <memory>
#include <span>

#include <SDL2/SDL_surface.h>

#include "color.hpp"

namespace plot {
  class Canvas {
   public:
    using Point = std::complex<double>;
    using View = SDL_Surface*;

    /**
     * Constructs a Canvas.
     *
     * \param firstPoint The value corresponding to one corner of the canvas
     * \param secondPoint The point corresponding to the opposite corner of the canvas
     * \param width The width in pixels of the canvas
     * \param height The height in pixels of the canvas to draw
     */
    Canvas(const Point& firstPoint,
           const Point& secondPoint,
           int width, int height);
    Canvas(const Canvas&);
    Canvas(Canvas&&) = default;
    ~Canvas() = default;
    Canvas& operator=(const Canvas&);
    Canvas& operator=(Canvas&&) = default;

    /** Returns the number of pixels wide the canvas is */
    size_t width() const { return width_; }
    /** Returns the number of pixels tall the canvas is */
    size_t height() const { return height_; }

    /** Accesses the color of the given complex point */
    [[deprecated]] Color& operator[](const Point& location);
    /** Accesses the color of the given complex point */
    [[deprecated]] const Color& operator[](const Point& location) const;
    /** Accesses the color of the pixel at the given (x,y) coordinate */
    Color& operator()(size_t x, size_t y);
    /** Accesses the color of the pixel at the given (x,y) coordinate */
    const Color& operator()(size_t x, size_t y) const;

    Point valueOf(size_t x, size_t y) const;

    /** Returns the maximum value of the canvas. */
    Point min() const { return min_; }
    /** Returns the minimum value of the canvas. */
    Point max() const { return max_; }
    /** The span of the whole canvas */
    Point span() const;
    /** The step size between adjacent pixels */
    Point step() const;

    /** Returns a view of the points */
    View getAllValues() const;

    std::span<Color> row(size_t y);

    Color* begin();
    Color* end();
    Color const* begin() const;
    Color const* end() const;

   private:
    std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> points_;
    int width_;
    int height_;

    Point min_;
    Point max_;

    static Point calculateMin(Point first, Point second);
    static Point calculateMax(Point first, Point second);

    std::pair<size_t, size_t> indexOf(const Point& location) const;
    Color* colorAt(void* pixels, size_t x, size_t y) const;
    Color* uncheckedColorAt(void* pixels, size_t x, size_t y) const;
  };
}  // namespace plot

#endif
