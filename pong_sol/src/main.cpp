#include <sgfx/key.hpp>
#include <sgfx/color.hpp>
#include <sgfx/canvas.hpp>
#include <sgfx/window.hpp>
#include <sgfx/primitives.hpp>
#include <sgfx/vec.hpp>

#include <algorithm>
#include <iostream>

#include <chrono>
#include <thread>
#include <cmath>

int main(int argc, char* argv[])
{
	using namespace sgfx;
	using namespace std::chrono_literals;

  // create window
  std::uint16_t ww {1024};
  std::uint16_t wh {768};
	window win {ww, wh};
	
  //
  // create entities
  auto bg_color {color::black};

  // left player
	canvas left_player {{20,200}};
  point left_player_pos {50, 384};
  auto left_player_v {10};
	std::fill_n(left_player.pixels(),
      left_player.width() * left_player.height(),
      color::gray);

  // ball
  uint16_t ball_rad {20};
  uint16_t ball_v {5};
	canvas ball {{std::uint16_t(ball_rad*2), std::uint16_t(ball_rad*2)}};
  vec ball_pos {ww/2.f, wh/2.f};
  vec ball_dir {1, 1};
  { // make ball shape
    using namespace std;
    auto p2 = [](uint16_t n) {return uint16_t(n*n);};
    for (uint16_t x=0; x<ball.width(); x++)
      for (uint16_t y=0; y<ball.height(); y++)
        plot(ball, {x, y},
            (p2(x-ball_rad) + p2(y-ball_rad) > p2(0.9*ball_rad)) ?
            bg_color : color::white);
  }
  
  //
  // enter loop and read input events
  while(win.handle_events() && !win.is_pressed(sgfx::key::escape))
	{
    //
    // update world state

    // move player
		if(win.is_pressed(key_id{'w'}))
      left_player_pos.y -= left_player_v;
		if(win.is_pressed(key_id{'s'}))
      left_player_pos.y += left_player_v;

    // move ball
    ball_pos = ball_pos + scale(ball_v, ball_dir);
    point b { uint16_t(ball_pos.x), uint16_t(ball_pos.y) };
    auto br = ball_rad;

    // check collision
    // TODO
    if (b.x <= 0 || b.x+2*br >= win.width())
      ball_dir = reflect(ball_dir, {1,0});
    if (b.y <= 0 || b.y+2*br >= win.height())
      ball_dir = reflect(ball_dir, {0,1});

    //
    // render
    clear(win, color::black);
    draw(win, left_player, left_player_pos);
    draw(win, ball, b);
		win.show();
	};

	return 0;
}
