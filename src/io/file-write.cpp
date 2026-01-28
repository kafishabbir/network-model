#include "io/file-write.h"

const std::string io::FileWrite::FOLDER_NAME_RUN = "run/";
const std::string io::FileWrite::FOLDER_NAME_FIGURES = "figures/";


void io::FileWrite::perform_folder_check_and_clear(
	const std::string& folder_path
)
{
	std::filesystem::remove_all(folder_path);
	std::filesystem::create_directories(folder_path);
	std::cout << folder_path << " -- used for io/file-wirte" << std::endl;
}

std::string io::FileWrite::generate_folder_path_for_output(
	const std::string& folder_or_result_name
)
{
	return FOLDER_NAME_RUN + folder_or_result_name + FOLDER_NAME_FIGURES;
}

void

void io::FileWrite::write_to_particular_folder_in_run(
	const std::vector<std::pair<std::string, std::string>>&
	vec_file_name_and_content,
	const std::string& folder_or_result_name
)
{
	const std::string folder_path_output =
		generate_folder_path_for_output(folder_or_result_name);

	perform_folder_check_and_clear(folder_path_output);

	for(const auto& [file_name, file_content]: vec_file_name_and_content)
	{
		std::ofstream fout(folder_path_output + file_name);
		fout << file_content;
	}
}

void io::FileWrite::flow(
	const std::vector<std::pair<std::string, std::string>>&
	vec_file_name_and_content
)
{
	write_to_particular_folder_in_run(vec_file_name_and_content, "flow/");
}
