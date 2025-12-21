#ifndef PLOT_FILE_PATH
#define PLOT_FILE_PATH

#include <string>
#include <sstream>
namespace plot
{
	class FilePath
	{
		static const std::string FOLDER_RUN_FLOW;
		static const std::string FOLDER_FIGURES;
		static const std::string FILE_TEX_LIST_FIGURES;
		static const std::string FILE_TEX_FIGURE_PART_NAME;
		static const std::string XX_FILE_TEX_EXTENSION;
		const int figure_index;

	public:
		FilePath(const int figure_index);
		static std::string file_list_figures();

		std::string path_for_io_and_exe() const;
		std::string path_for_latex() const;
		std::string file_name_without_tex() const;
		std::string file_name_with_tex() const;
	};
}

#endif
