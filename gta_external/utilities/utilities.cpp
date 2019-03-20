#include "utilities.hpp"

int utilities::get_frame_rate()
{
	static int i_fps, i_last_fps;
	static float fl_last_tick_count, fl_tick_count;
	fl_tick_count = clock() * 0.001f;
	i_fps++;
	if ((fl_tick_count - fl_last_tick_count) >= 1.0f)
	{
		fl_last_tick_count = fl_tick_count;
		i_last_fps = i_fps;
		i_fps = 0;
	}
	return i_last_fps;
};