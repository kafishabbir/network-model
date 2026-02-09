#include "visualize/latex.h"

std::string visualize::Latex::command(
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

std::string visualize::Latex::scope_base(
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

	ss << commands << '\n';

	ss << command("end", scope_name) << '\n';
	return ss.str();
}

std::string visualize::Latex::begin_end_figure_scope(
	const std::string& file_name,
	const std::string& caption
)
{
	std::stringstream ss;
	ss << command("centering") << '\n';
	ss << command("input", file_name) << '\n';
	ss << command("caption", caption) << '\n';
	ss << command("label", file_name);
	return scope_base("figure", ss.str(), "H");
}


std::string visualize::Latex::begin_end_document_scope(
	const std::string& file_name_of_tex_code_for_input
)
{
	const auto& command_input_list_figures = command("input", file_name_of_tex_code_for_input);
	return scope_base("document", command_input_list_figures);
}

std::string visualize::Latex::scope_tikzpicture(
	const std::string& tex_code_drawing_shapes
)
{
	return scope_base("tikzpicture", tex_code_drawing_shapes, "scale=\\imagewidthscale");

}

std::string visualize::Latex::scope_shift_and_rotate(
	const double shift_to_x,
	const double shift_to_y,
	const double rotate_angle,
	const std::string& draw_commands_to_be_scoped
)
{
	std::stringstream ss;
	ss << "shift={(" << shift_to_x << ", " << shift_to_y << ")}";
	ss << ", rotate=" << rotate_angle;

	return scope_base("scope", draw_commands_to_be_scoped, ss.str());
}
