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

std::string visualize::Latex::scope(
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

std::string visualize::Latex::begin_end_figure_scope(
	const std::string& file_name,
	const std::string& caption
)
{
	std::stringstream ss;
	ss << command("centering") << '\n';
	ss << command("input", file_name) << '\n';
	ss << command("caption", caption) << '\n';
	ss << command("label", file_name) << '\n';
	return scope("figure", ss.str(), "H");
}
