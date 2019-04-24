#include <sgfx/canvas.hpp>

void sgfx::draw(window& target, const canvas& img, point top_left)
{
  // window dimensions
  const auto ww { target.width() };
  const auto wh { target.height() };

  // canvas dimensions
  const auto cw { img.width() };
  const auto ch { img.height() };

  // start point dimensions
  const auto tlx { top_left.x };
  const auto tly { top_left.y };

  for (auto x=0; x<cw*ch; x++) {
    point p { std::uint16_t(tlx+(x%cw)), std::uint16_t(tly+(x/cw)) };
    const auto idx { p.toIdx(ww, wh) };
    target.pixels()[idx] = img.pixels()[x];
  }
}
