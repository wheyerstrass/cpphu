#include <sgfx/key.hpp>
#include <sgfx/color.hpp>
#include <sgfx/canvas.hpp>
#include <sgfx/window.hpp>
#include <sgfx/primitives.hpp>
#include <sgfx/vec.hpp>
#include <sgfx/utils.hpp>

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
  vec left_player_pos {50, 384};
  auto left_player_v {10};
	std::fill_n(left_player.pixels(),
      left_player.width() * left_player.height(),
      color::cyan);

  // right player
	canvas right_player {{20,200}};
  vec right_player_pos {1024-50, 384};
  auto right_player_v {10};
	std::fill_n(right_player.pixels(),
      right_player.width() * right_player.height(),
      color::magenta);


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
            color::lucent : color::white);
  }

  auto renderFrame = [&]() {
    clear(win, color::black);
    draw(win, left_player, vecToPoint(left_player_pos));
    draw(win, right_player, vecToPoint(right_player_pos));
    point bp = vecToPoint(ball_pos);
    bp.x -= ball_rad;
    bp.y -= ball_rad;
    draw(win, ball, bp);
		win.show();
  };

  renderFrame();
  
  //
  // enter loop and read input events
  auto br = ball_rad;
  bool pause { true };
  while(win.handle_events() && !win.is_pressed(sgfx::key::escape))
	{
    //
    // update world state
    if (win.is_pressed(sgfx::key::space))
      pause = false;

    if (pause)
      continue;
    

    // move player
		if(win.is_pressed(key_id{'w'}))
      left_player_pos.y -= left_player_v;
		if(win.is_pressed(key_id{'s'}))
      left_player_pos.y += left_player_v;
		if(win.is_pressed(key_id{'j'}))
      right_player_pos.y += right_player_v;
		if(win.is_pressed(key_id{'k'}))
      right_player_pos.y -= right_player_v;

    // move ball
    ball_pos = ball_pos + scale(ball_v, ball_dir);

    //
    // check ball collision

    // with left/right wall
    if (ball_pos.x-br <= 0 || ball_pos.x+br >= win.width())
      ball_dir = reflect(ball_dir, {1,0});

    // with top/bottom wall
    if (ball_pos.y-br <= 0 || ball_pos.y+br >= win.height())
      ball_dir = reflect(ball_dir, {0,1});

    // with left player
    if (ball_pos.x-br <= left_player_pos.x+left_player.width() &&
        ball_pos.x-br >= left_player_pos.x &&
        ball_pos.y <= left_player_pos.y+left_player.height() &&
        ball_pos.y >= left_player_pos.y)
      ball_dir = reflect(ball_dir, {1,0});
    
    // with right player
    if (ball_pos.x+br <= right_player_pos.x+right_player.width() &&
        ball_pos.x+br >= right_player_pos.x &&
        ball_pos.y <= right_player_pos.y+right_player.height() &&
        ball_pos.y >= right_player_pos.y)
      ball_dir = reflect(ball_dir, {1,0});

    // bind players to window
    //
    // left player
    if (left_player_pos.y <= 0)
      left_player_pos.y = 0;
    else if (left_player_pos.y+left_player.height() > win.height())
      left_player_pos.y = win.height()-left_player.height();
    // right player
    if (right_player_pos.y <= 0)
      right_player_pos.y = 0;
    else if (right_player_pos.y+right_player.height() > win.height())
      right_player_pos.y = win.height()-right_player.height();

    //
    // render
    renderFrame();
	};

	return 0;
}
