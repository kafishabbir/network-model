#ifndef PLOT_LATEX_CODE_H
#define PLOT_LATEX_CODE_H

#include <string>
#include <sstream>

namespace plot
{
	class LatexCode
	{
		static std::string command(
			const std::string& command_name,
			const std::string& command_body = ""
		);


	public:

		static std::string scope(
			const std::string& scope_name,
			const std::string& commands,
			const std::string& scope_arguments = ""
		);

		static std::string scope_figure(
			const std::string& file_input_tikz_code_single_plot,
			const std::string& caption_figure
		);

		static std::string tikz_scope_shift_rotate(
			const double x,
			const double y,
			const double angle,
			const std::string& draw_commands
		);

		static std::string tikz_string_one_filled_rectangle(
			const std::string& color,
			const double x1,
			const double y1,
			const double x2,
			const double y2
		);
	};
}


#endif
