#ifndef SGFX_PRIMITIVE_TYPES_H
#define SGFX_PRIMITIVE_TYPES_H

#include <cmath>
#include <cstdint>

namespace sgfx
{
  struct vec
  {
  };

  struct point
  {
    std::uint16_t x;
    std::uint16_t y;

    /*
     * Transform sgfx::point coordinates from
     * [0, width-1] x [0, height-1]
     * to
     * array index for sgfx::window::pixels
     */
    std::uint32_t toIdx(std::uint16_t width, std::uint16_t height)
    {
      auto x_{x};
      x_ = std::fmax(x_, 0);
      x_ = std::fmin(x_, width);

      auto y_{y};
      y_ = std::fmax(y_, 0);
      y_ = std::fmin(y_, height);

      return std::uint32_t(x_ + y_*width); // TODO: fix overflow 
    }
  };

  struct dimension
  {
    std::uint16_t x;
    std::uint16_t y;
  };

  struct rectangle
  {
    point top_left;
    dimension size;
  };
}

#endif
