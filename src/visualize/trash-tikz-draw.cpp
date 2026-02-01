#include "visualize/tikz-draw.h"

std::string visualize::TikzDraw::rectangle(
	const std::string& color,
	const double x1,
	const double y1,
	const double x2,
	const double y2
)
{
	std::stringstream ss;
	ss << "\\fill" << "[" << color << "]";
	ss << "(" << x1 << ", " << y1 << ")";
	ss << " rectangle" << " ";
	ss << "(" << x2 << ", " << y2 << ")" << ";";
	return ss.str();
}



std::string visualize::TikzDraw::scope(
	const double shift_to_x,
	const double shift_to_y,
	const double rotate_angle,
	const std::string& draw_commands_to_be_scoped
)
{
	std::stringstream ss;
	ss << "shift={(" << shift_to_x << ", " << shift_to_y << ")}";
	ss << ", rotate=" << rotate_angle;

	return visualize::Latex::scope("scope", draw_commands_to_be_scoped, ss.str());
}
