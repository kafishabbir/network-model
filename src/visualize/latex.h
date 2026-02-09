#ifndef VISUALIZE_LATEX_H
#define VISUALIZE_LATEX_H

#include <string>
#include <sstream>

namespace visualize
{
	class Latex
	{
		/*
		begin{scope_name}[scope_arguments]
			commands...
		end{scope_name}
		*/
		static std::string scope_base(
			const std::string& scope_name,
			const std::string& commands,
			const std::string& scope_arguments = ""
		);

	public:
		// command_name{command_body}
		static std::string command(
			const std::string& command_name,
			const std::string& command_body = ""
		);


		/*
		begin{figure}[H]
		  centering
		  input{figure/fig-1}
		  caption{}
		end{figure}
		*/
		static std::string begin_end_figure_scope(
			const std::string& file_name_of_tikz_code_for_input,
			const std::string& caption
		);

		/*
		begin{document}
			input{figures/list-figures}
		end{document}
		*/

		static std::string begin_end_document_scope(
			const std::string& file_name_of_tex_code_for_input
		);

		/*
		begin{tikzpicture}[scale=\imagewidthscale]
			tex_code_drawing_shapes
		end{tikzpicture}
		*/
		static std::string scope_tikzpicture(
			const std::string& tex_code_drawing_shapes
		);

		/*
		begin{scope}[shift={(x, y)}, rotate=angle]
			draw_commands_to_scope
		end{scope}
		*/
		static std::string scope_shift_and_rotate(
			const double shift_to_x,
			const double shift_to_y,
			const double rotate_angle,
			const std::string& draw_commands_to_scope
		);
	};
}

#endif
