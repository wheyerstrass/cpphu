#include <sgfx/color.hpp>
#include <sgfx/primitives.hpp>
#include <sgfx/window.hpp>

#include <chrono>
#include <thread>

int main(int argc, char* argv[])
{
	using namespace sgfx;
	using namespace std::chrono_literals;
	
	window main_window{256,256};
	
	//plot(main_window,{10,10},color::red);
	//plot(main_window,{10,110},color::green);
	//plot(main_window,{110,10},color::blue);
	//plot(main_window,{110,110},color::yellow);
	
	//main_window.show();
	//std::this_thread::sleep_for(2s);

	clear(main_window,color::black);
	main_window.show();
	
	std::this_thread::sleep_for(1s);
	
	hline(main_window,{20,127},256, color::white);
	main_window.show();
	
	std::this_thread::sleep_for(1s);
	
	vline(main_window,{127,127},256, color::white);
	main_window.show();
	
	std::this_thread::sleep_for(2s);
	
	fill(main_window,{{127,127},{32,32}}, color::white);
	main_window.show();
	
	std::this_thread::sleep_for(2s);
	
	//line(main_window,{0,10},{127,127}, color::green);
	//line(main_window,{127,127},{246,0},color::blue);
	//main_window.show();
	
	std::this_thread::sleep_for(2s);

	return 0;
}
