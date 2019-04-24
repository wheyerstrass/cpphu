#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>

using namespace std;

namespace sgfx
{
  /* 
   * log utilities */
  template<typename Arg>
    inline void log(Arg arg)
    {
      cout << arg << flush;
    }

  template<typename Arg, typename... Args>
    inline void log(Arg arg, Args... args)
    {
      cout << arg << " ";
      log(args...);
    }

  /*
   * Transform sgfx::point coordinates from
   * [0, win_width-1] x [0, win_height-1]
   * to
   * array index for sgfx::window::pixels
   */
  std::uint16_t pointToPixelIndex(window& win, point p)
  {
    p.x = std::fmax(p.x, 0);
    p.x = std::fmin(p.x, win.width());

    p.y = std::fmax(p.y, 0);
    p.y = std::fmin(p.y, win.height());

    //
    // TODO: fix overflow 
    return std::fmin(p.x + p.y*win.width(), UINT16_MAX-1);
  }
}

#endif
