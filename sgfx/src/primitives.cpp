#include <sgfx/primitives.hpp>
#include <sgfx/utils.hpp>

#include <stdexcept>
#include <cmath>

void sgfx::plot(window& target, point p, color::rgb_color col)
{
  auto idx = pointToPixelIndex(target, p);
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
  const auto startPointX = p.x;
  const auto startPointY = p.y;

  for (auto l=0; l<length; l++) {
    const point currPoint { std::uint16_t(startPointX + l), startPointY };
    const auto idx = pointToPixelIndex(target, currPoint);
    target.pixels()[idx] = col;
  }
}

void sgfx::vline(window& target, point p, std::uint16_t length, color::rgb_color col)
{
  const auto startPointX = p.x;
  const auto startPointY = p.y;

  for (auto l=0; l<length; l++) {
    const point currPoint { startPointX, std::uint16_t(startPointY + l) };
    const auto idx = pointToPixelIndex(target, currPoint);
    target.pixels()[idx] = col;
  }
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
      const auto currIdx = pointToPixelIndex(target, currPoint);
      target.pixels()[currIdx] = col;
    }
  }
}

void sgfx::line(window& target, point p0, point p1, color::rgb_color col)
{
  const auto deltax { p1.x - p0.x }; // TODO vline
  const auto deltay { p1.y - p0.y }; // TODO hline

  const auto deltaySign { deltay >= 0 ? 1 : -1 };
  const auto deltaerr { std::abs( double(deltay) / double(deltax) ) };
  auto err { 0.0 };
  auto y { p0.y };

  for (auto x=p0.x; x<=p1.x; x++) {
    point p {x,y};
    plot(target, p, col);
    err += deltaerr;
    if (err >= 0.5) {
      y += deltaySign;
      err -= 1.0;
    }
  }
}
