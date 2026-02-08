#ifndef VISUALIZE_LATEX_H
#define VISUALIZE_LATEX_H

#include <string>
#include <sstream>

namespace visualize
{
	class Latex
	{

	public:
		// command_name{command_body}
		static std::string command(
			const std::string& command_name,
			const std::string& command_body = ""
		);

		// begin{scope_name}[scope_arguments]
		// 		commands...
		// end{scope_name}
		static std::string scope(
			const std::string& scope_name,
			const std::string& commands,
			const std::string& scope_arguments = ""
		);

		// begin{figure}[H]
		//   centering
		//   input{figure/fig-1}
		//   caption{}
		// end{figure}
		static std::string begin_end_figure_scope(
			const std::string& file_name_of_tikz_code_for_input,
			const std::string& caption
		);

		static std::string begin_end_document_scope(
			const std::string& file_name_of_tex_code_for_input
		);


	};
}

#endif
