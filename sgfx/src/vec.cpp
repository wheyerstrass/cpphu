#include <sgfx/vec.hpp>


vec scale(const float_t& s, const vec& v)
{
  return vec {s*v.x, s*v.y};
}

float_t dot(const vec& v1, const vec& v2)
{
  return (v1.x*v2.x + v1.y*v2.y);
}

vec reflect(const vec& v, const vec& n)
{
  return v - scale( 2 * dot(v, n), n);
}

std::ostream& operator << (std::ostream& os, const vec& v)
{
  return os << "vec(" << v.x << "," << v.y << ")";
}
