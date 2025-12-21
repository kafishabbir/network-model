#include "plot/latexcode.h"

std::string plot::LatexCode::tikz_string_one_filled_rectangle(
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
	ss << " rectangle ";
	ss << "(" << x2 << ", " << y2 << ")" << ";";
	return ss.str();
}

std::string plot::LatexCode::tikz_scope_shift_rotate(
	const double x,
	const double y,
	const double angle,
	const std::string& draw_commands
)
{
	std::stringstream ss;
	ss << "shift={(" << x << ", " << y << ")}";
	ss << ", rotate=" << angle;

	return scope("scope", draw_commands, ss.str());
}


std::string plot::LatexCode::command(
	const std::string& command_name,
	const std::string& command_body
)
{
	std::stringstream ss;
	ss << '\\' << command_name;
	if(!command_body.empty())
	{
		ss << '{' << command_body << '}';
	}

	return ss.str();
}

std::string plot::LatexCode::scope(
	const std::string& scope_name,
	const std::string& commands,
	const std::string& scope_arguments
)
{
	std::stringstream ss;
	ss << command("begin", scope_name);
	if(!scope_arguments.empty())
	{
		ss << '[' << scope_arguments << ']';
	}
	ss << '\n';

	ss << commands;

	ss << command("end", scope_name) << '\n';
	return ss.str();
}

std::string plot::LatexCode::scope_figure(
	const std::string& file_input_tikz_code_single_plot,
	const std::string& caption_figure
)
{
	std::stringstream ss;
	ss << command("centering") << '\n';
	ss << command("input", file_input_tikz_code_single_plot) << '\n';
	ss << command("caption", caption_figure) << '\n';

	return scope("figure", ss.str(), "H");
}
