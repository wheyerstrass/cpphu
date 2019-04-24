#ifndef SGFX_PRIMITIVES_H
#define SGFX_PRIMITIVES_H

#include <sgfx/primitive_types.hpp>
#include <sgfx/window.hpp>

#include <cmath>
#include <cstdint>

namespace sgfx
{
  template<typename DrawTarget>
    void plot(DrawTarget& target, point p, color::rgb_color col)
    {
      auto idx = p.toIdx(target.width(), target.height());
      target.pixels()[idx] = col;
    }

  template<typename DrawTarget>
    void clear(DrawTarget& target, color::rgb_color col)
    {
      const auto ww = target.width();
      const auto wh = target.height();
      for(auto i=0; i<ww*wh; i++)
        target.pixels()[i] = col;
    }

  template<typename DrawTarget>
    void hline(DrawTarget& target, point p, std::uint16_t length, color::rgb_color col)
    {
      const auto startPointX = p.x;
      const auto startPointY = p.y;
      length = fmin(length, target.width()-startPointX);

      for (auto l=0; l<length; l++) {
        point p { uint16_t(startPointX + l), startPointY };
        const auto idx = p.toIdx(target.width(), target.height());
        target.pixels()[idx] = col;
      }
    }

  template<typename DrawTarget>
    void vline(DrawTarget& target, point p, std::uint16_t length, color::rgb_color col)
    {
      const auto startPointX = p.x;
      const auto startPointY = p.y;
      length = fmin(length, target.height()-startPointY);

      for (auto l=0; l<length; l++) {
        point p { startPointX, uint16_t(startPointY + l) };
        const auto idx = p.toIdx(target.width(), target.height());
        target.pixels()[idx] = col;
      }
    }

  template<typename DrawTarget>
    void fill(DrawTarget& target, rectangle rect, color::rgb_color col)
    {
      const auto startPointX {rect.top_left.x};
      const auto startPointY {rect.top_left.y};

      for (auto y=0; y<rect.size.y; y++) {
        for (auto x=0; x<rect.size.x; x++) {
          point p { uint16_t(startPointX + x), uint16_t(startPointY + y) };
          const auto idx = p.toIdx(target.width(), target.height());
          target.pixels()[idx] = col;
        }
      }
    }

  template<typename DrawTarget>
    void line(DrawTarget& target, point p0, point p1, color::rgb_color col)
    {
      const auto deltax { p1.x - p0.x }; // TODO vline
      const auto deltay { p1.y - p0.y }; // TODO hline

      const auto deltaySign { deltay >= 0 ? 1 : -1 };
      const auto deltaerr { abs( double(deltay) / double(deltax) ) };
      auto err { 0.0 };
      auto y { p0.y };

      for (auto x=p0.x; x<=p1.x; x++) {
        plot(target, {x,y}, col);
        err += deltaerr;
        if (err >= 0.5) {
          y += deltaySign;
          err -= 1.0;
        }
      }
    }
}

#endif
