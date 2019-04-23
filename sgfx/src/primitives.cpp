#include <sgfx/primitives.hpp>

#include <stdexcept>

/*
 * Transform window coordinates from
 * [0, win_width-1] x [0, win_height-1]
 * to
 * array index for sgfx::window::pixels
 * ( throws custom Out-Of-Bounds-Error )
 */
auto coordToPixelIdx(
    std::uint16_t px,
    std::uint16_t py,
    std::uint16_t ww,
    std::uint16_t wh) {
  if((px < 0 || px > ww-1) || (py < 0 || py > wh-1))
    throw std::runtime_error("Point outside window dimenstion");
  return (px + ww*py);
}

void sgfx::plot(window& target, point p, color::rgb_color col)
{
  const auto idx = coordToPixelIdx(p.x, p.y,
      target.width(), target.height());
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
  const auto idx = coordToPixelIdx(p.x, p.y,
      target.width(), target.height());
  for(auto i=idx; i<(idx+length); i++)
    target.pixels()[i] = col;
}

void sgfx::vline(window& target, point p, std::uint16_t length, color::rgb_color col)
{
}

void sgfx::fill(window& target, rectangle rect, color::rgb_color col)
{
}

void sgfx::line(window& target, point p0, point p1, color::rgb_color col)
{
}
