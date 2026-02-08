#include "visualize/draw.h"

std::string visualize::Draw::arrow(
	const double x_begin,
	const double x_end,
	const double y
)
{
	std::stringstream ss;
	ss << "\\draw[->] (" << x_begin << ", " << y << ")";
	ss << " -- ";
	ss << "(" << x_end << ", " << y << ");";
	return ss.str();
}


std::string visualize::Draw::num(const double val)
{
	std::stringstream ss;
	ss << "\\num{";
	ss << std::setprecision(3) << val;
	ss << "}";
	return ss.str();
}


std::string visualize::Draw::mpos_horizontal_rectangles(
	const nst::Tube& tube,
	const std::vector<std::string>& colors
)
{
	const std::vector<double>& v = tube.mpos;
	const int fluid_first = tube.fluid_first;
	const double radius = tube.radius;

	const int n = v.size();
	std::stringstream ss;
	for(int i = 1; i < n; ++ i)
	{
		const auto& color = colors[(i + fluid_first + 1) % 2];
		const double x1 = v[i - 1];
		const double y1 = radius;
		const double x2 = v[i];
		const double y2 = - radius;
		const auto& tikz_str_single_fluid_block =
			rectangle(color, x1, y1, x2, y2);

		ss << tikz_str_single_fluid_block << '\n';
	}
	return ss.str();
}


std::string visualize::Draw::circle(
	const double x,
	const double y,
	const double radius
)
{
	std::stringstream ss;
	ss << "\\draw" << "(" << x << ", " << y << ") " << "circle" << "(" << radius << ")" << ";";
	return ss.str();
}

std::string visualize::Draw::node(
	const double x,
	const double y,
	const std::string& node_text
)
{
	std::stringstream ss;
	ss << "\\node" << " at " << "(" << x << ", " << y << ") " << "{" << node_text << "}" << ";";
	return ss.str();
}


std::string visualize::Draw::rectangle(
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



std::string visualize::Draw::scope_shift_and_rotate(
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

