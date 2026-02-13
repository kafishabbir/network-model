#include "visualize/draw.h"

std::string visualize::Draw::d(const double val)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(3) << val;
	return ss.str();
}

std::string visualize::Draw::arrow(
	const double x_begin,
	const double x_end,
	const double y
)
{
	std::stringstream ss;
	ss << "\\draw[->] (" << d(x_begin) << ", " << d(y) << ")";
	ss << " -- ";
	ss << "(" << d(x_end) << ", " << d(y) << ");";
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
	const std::vector<double>& v = tube.visual.mpos;
	const int id_fluid_first = tube.id_fluid_first;
	const double radius = tube.visual.radius;

	const int n = v.size();
	std::stringstream ss;
	for(int i = 1; i < n; ++ i)
	{
		const auto& color = colors[(i + id_fluid_first + 1) % 2];
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
	ss << "\\draw" << "(" << d(x) << ", " << d(y) << ") " << "circle" << "(" << d(radius) << ")" << ";";
	return ss.str();
}

std::string visualize::Draw::node(
	const double x,
	const double y,
	const std::string& node_text
)
{
	std::stringstream ss;
	ss << "\\node" << " at " << "(" << d(x) << ", " << d(y) << ") " << "{" << node_text << "}" << ";";
	return ss.str();
}

std::string visualize::Draw::node_long(
	const double x,
	const double y,
	const std::string& node_text
)
{
	std::stringstream ss;
	ss << "\\node[right, align=left]" << " at " << "(" << d(x) << ", " << d(y) << ") " << "{" << node_text << "}" << ";";
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
	ss << "(" << d(x1) << ", " << d(y1) << ")";
	ss << " rectangle" << " ";
	ss << "(" << d(x2) << ", " << d(y2) << ")" << ";";
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
	ss << "shift={(" << d(shift_to_x) << ", " << d(shift_to_y) << ")}";
	ss << ", rotate=" << d(rotate_angle);

	return Latex::scope_base("scope", draw_commands_to_be_scoped, ss.str());
}

