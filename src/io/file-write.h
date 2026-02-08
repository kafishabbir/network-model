#ifndef IO_FILE_WRITE_H
#define IO_FILE_WRITE_H

#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

namespace io
{
    class FileWrite
    {
		static const std::string FOLDER_NAME_RESULTS;
		static const std::string FILE_NAME_TEMPLATE;
		static const std::string FOLDER_NAME_FIGURES;
		static const std::string FOLDER_NAME_OUTPUT;

		static std::string generate_folder_path_for_output(
			const std::string& folder_or_result_name
		);

		static std::string generate_folder_path_root(
			const std::string& folder_or_result_name
		);

		static void perform_folder_check_and_clear(
			const std::string& folder_or_result_name
		);

		static void write_to_particular_folder_in_run(
			const std::vector<str_pair>& file_name_and_content_v,
			const std::string& folder_or_result_name
		);

        public:

        static void flow(
			const std::vector<str_pair>& file_name_and_content_v
		);
    };
}

#endif
