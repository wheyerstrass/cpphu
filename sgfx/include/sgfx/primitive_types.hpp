#ifndef SGFX_PRIMITIVE_TYPES_H
#define SGFX_PRIMITIVE_TYPES_H

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
	};
	
	struct dimension
	{
	};
	
	struct rectangle
	{
		point top_left;
		dimension size;
	};
}

#endif
