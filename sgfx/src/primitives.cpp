#include <sgfx/primitives.hpp>

#include <stdexcept>
#include <cmath>

void sgfx::plot(window& target, point p, color::rgb_color col)
{
  auto idx = target.pointToPixelIndex(p);
  target.pixels()[idx] = col;
}

void sgfx::clear(window& target, color::rgb_color col)
{
  const auto ww = target.width();
  const auto wh = target.height();
  for(auto i=0; i<ww*wh; i++)
    target.pixels()[i] = col;
}

void sgfx::hline(window& target, point p, std::uint16_t length, color::rgb_color col)
{
  const auto startIdx = target.pointToPixelIndex(p);
  const auto endIdx = target.pointToPixelIndex({std::uint16_t(p.x+length), p.y});

  for (auto i=startIdx; i<endIdx; i++)
    target.pixels()[i] = col;
}

void sgfx::vline(window& target, point p, std::uint16_t length, color::rgb_color col)
{
  const auto startIdx = target.pointToPixelIndex(p);
  const auto endIdx = target.pointToPixelIndex({p.x, std::uint16_t(p.y+length)});

  const auto ww = target.width();
  for (auto i=startIdx; i<endIdx; i+=ww)
    target.pixels()[i] = col;
}

void sgfx::fill(window& target, rectangle rect, color::rgb_color col)
{
  const auto startPointX {rect.top_left.x};
  const auto startPointY {rect.top_left.y};

  for (auto y=0; y<rect.size.y; y++) {
    for (auto x=0; x<rect.size.x; x++) {
      const point currPoint {
        std::uint16_t(startPointX + x),
        std::uint16_t(startPointY + y)
      };
      const auto currIdx = target.pointToPixelIndex(currPoint);
      target.pixels()[currIdx] = col;
    }
  }
}

void sgfx::line(window& target, point p0, point p1, color::rgb_color col)
{
}
