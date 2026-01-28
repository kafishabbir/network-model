#include "visualize/latex-basic-commands.h"

std::string visualize::LatexBasicCommands::command(
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

std::string visualize::LatexBasicCommands::scope(
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

std::string visualize::LatexBasicCommands::begin_end_figure_with_captions(
	const std::string& file_name_of_tikz_code_for_input,
	const std::string& caption
)
{
	std::stringstream ss;
	ss << command("centering") << '\n';
	ss << command("input", file_name_of_tikz_code_for_input) << '\n';
	ss << command("caption", caption) << '\n';

	return scope("figure", ss.str(), "H");
}
