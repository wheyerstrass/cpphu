#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>

namespace util
{
  /* 
   * logging utilities */
  template<typename Arg>
    inline void log(Arg arg)
    {
      std::cout << arg << std::endl;
    }

  template<typename Arg, typename... Args>
    inline void log(Arg arg, Args... args)
    {
      std::cout << arg << " ";
      util::log(args...);
    }
}

#endif
