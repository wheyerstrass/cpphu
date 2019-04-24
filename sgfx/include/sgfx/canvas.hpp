#ifndef SGFX_CANVAS_H
#define SGFX_CANVAS_H

#include <sgfx/color.hpp>
#include <sgfx/primitive_types.hpp>
#include <sgfx/window.hpp>


namespace sgfx
{
	class canvas
	{
		public:
		explicit canvas(dimension size):
      width_{size.x},
      height_{size.y},
      pixels_(size.x * size.y)
    {};
		
		std::uint16_t width() const { return width_; };
		std::uint16_t height() const { return height_; };
		
		color::rgb_color* pixels() { return pixels_.data(); };
		const color::rgb_color* pixels() const { return pixels_.data(); };
		
    private:
    const std::uint16_t width_, height_;
		std::vector<color::rgb_color> pixels_;
	};
	
	void draw(window& target, const canvas& img, point top_left);
}

#endif
