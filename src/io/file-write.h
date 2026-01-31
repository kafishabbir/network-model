#ifndef IO_FILE_WRITE_H
#define IO_FILE_WRITE_H

#include <filesystem>
#include <iostream>

namespace io
{
    class FileWrite
    {
		static const std::string FOLDER_NAME_RUN = "run/";
		static const std::string FOLDER_NAME_FIGURES = "figures/";

		static std::string generate_folder_path_for_output(
			const std::string& folder_or_result_name
		);

		static void perform_folder_check_and_clear(
			const std::string& folder_path
		);

		static void write_to_particular_folder_in_run(
			const std::vector<std::pair<std::string, std::string>>&
			file_name_and_content_v,
			const std::string& folder_or_result_name
		);

        public:

        static void flow(
			const std::vector<std::pair<std::string, std::string>>&
			file_name_and_content_v
		);
    };
}

#endif
