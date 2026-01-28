#ifndef VISUALIZE_FLOW_FILE_OUT
#define VISUALIZE_FLOW_FILE_OUT

#include <string>
#include <sstream>
namespace visualize
{
	class FlowFileOut
	{
		static const std::string FOLDER_RUN_FLOW;
		static const std::string FOLDER_FIGURES;
		static const std::string FILE_TEX_LIST_FIGURES;
		static const std::string FILE_TEX_FIGURE_PART_NAME;
		static const std::string XX_FILE_TEX_EXTENSION;
		const int figure_index;

	public:
		FlowFileOut(const int figure_index);

		static std::string file_list_figures();
		std::string file_name() const;
		std::string file_name_with_tex_extension() const;
		std::string path() const;
		std::string path_for_latex_input() const;

	};
}

#endif
