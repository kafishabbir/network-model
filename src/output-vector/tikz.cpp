#include "output-vector/tikz.h"
#include "output/latex.h"

std::string output_vector::Tikz::arrow(
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

std::string output_vector::Tikz::circle(
	const double x,
	const double y,
	const double radius
)
{
	std::stringstream ss;
	ss << "\\draw" << "(" << d(x) << ", " << d(y) << ") " << "circle" << "(" << d(radius) << ")" << ";";
	return ss.str();
}

std::string output_vector::Tikz::node(
	const double x,
	const double y,
	const std::string& node_text
)
{
	std::stringstream ss;
	ss << "\\node" << " at " << "(" << d(x) << ", " << d(y) << ") " << "{" << node_text << "}" << ";";
	return ss.str();
}

std::string output_vector::Tikz::node_long(
	const double x,
	const double y,
	const std::string& node_text
)
{
	std::stringstream ss;
	ss << "\\node[right, align=left]" << " at " << "(" << d(x) << ", " << d(y) << ") " << "{" << node_text << "}" << ";";
	return ss.str();
}

std::string output_vector::Tikz::rectangle(
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

std::string output_vector::Tikz::scope_shift_and_rotate(
	const double shift_to_x,
	const double shift_to_y,
	const double rotate_angle,
	const std::string& draw_commands_to_be_scoped
)
{
	std::stringstream ss;
	ss << "shift={(" << d(shift_to_x) << ", " << d(shift_to_y) << ")}";
	ss << ", rotate=" << d(rotate_angle);

	return output::Latex::scope_base("scope", draw_commands_to_be_scoped, ss.str());
}

