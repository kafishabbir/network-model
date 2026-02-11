#ifndef IO_FILE_WRITE_H
#define IO_FILE_WRITE_H

#include "visualize/menu.h"

#include <filesystem>
#include <fstream>

/*
 * run/results/flow:
 * 	figures/
 * 		list-figures.tex
 * 		figure-1001.tex
 * 		figure-1002.tex
 * 		...
 * 	output/
 * 	flow.tex (main.tex)
 * 	Makefile
 */

namespace io
{
    class FileWrite
    {
		static std::string generate_folder_path_figures(
			const std::string& folder_or_result_name
		);

		static std::string generate_folder_path_root(
			const std::string& folder_or_result_name
		);

		static void clear_result_and_generate_folders(
			const std::string& folder_or_result_name
		);

		static std::string makefile_text(
			const std::string& folder_or_result_name
		);

		static std::string main_tex_text(
			const std::string& file_name_list_figures
		);

		static void create_makefile_and_main_tex(
			const std::string& folder_or_result_name,
			const std::string& file_name_list_figures
		);

		static void write_to_particular_folder_in_run(
			const std::vector<dst::str_pair>& file_name_and_content_v,
			const std::string& folder_or_result_name
		);

        public:

        static void flow(
			const std::vector<dst::str_pair>& file_name_and_content_v
		);
    };
}

#endif
