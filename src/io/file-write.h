#ifndef IO_FILE_WRITE_H
#define IO_FILE_WRITE_H

#include "global/dst.h"
#include "visualize/latex.h"

#include <filesystem>
//#include <iostream>
#include <fstream>
//#include <vector>


namespace io
{
    class FileWrite
    {
		static const std::string FOLDER_NAME_RESULTS;
		static const std::string FILE_NAME_TEMPLATE;
		static const std::string FOLDER_NAME_FIGURES;
		static const std::string FOLDER_NAME_OUTPUT;

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
			const std::vector<global::str_pair>& file_name_and_content_v,
			const std::string& folder_or_result_name
		);

        public:

        static void flow(
			const std::vector<global::str_pair>& file_name_and_content_v
		);
    };
}

#endif
