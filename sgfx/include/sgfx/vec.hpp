#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <cstdint>
#include <ostream>


struct vec
{
  float_t x;
  float_t y;

  vec operator + (const vec& v) const
  {
    return vec {x+v.x, y+v.y};
  }

  vec operator - (const vec& v) const
  {
    return vec {x-v.x, y-v.y};
  }

  vec operator * (const vec& v) const
  {
    return vec {x-v.x, y-v.y};
  }

  vec norm(void) const
  {
    float_t len = std::sqrt(x*x + y*y);
    return vec {x/len, y/len};
  }
};

vec scale(const float_t& s, const vec& v);
float_t dot(const vec& v1, const vec& v2);
vec reflect(const vec& v, const vec& n);
std::ostream& operator << (std::ostream& os, const vec& v);

#endif
