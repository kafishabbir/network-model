#include "output/latex.h"

std::string output::Latex::command(
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

std::string output::Latex::scope_base(
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

std::string output::Latex::begin_end_figure_scope(
	const std::string& command_code,
	const std::string& caption,
	const std::string& file_name
)
{
	std::stringstream ss;
	ss << command("centering") << '\n';
	ss << command_code << '\n';
	ss << command("caption", caption) << '\n';
	ss << command("label", "fig:" + file_name);
	return scope_base("figure", ss.str(), "H");
}


std::string output::Latex::begin_end_document_scope(
	const std::string& s
)
{
	return scope_base("document", s);
}

std::string output::Latex::scope_tikzpicture(
	const std::string& tex_code_drawing_shapes
)
{
	return scope_base("tikzpicture", tex_code_drawing_shapes, "scale=\\imagewidthscale");

}
