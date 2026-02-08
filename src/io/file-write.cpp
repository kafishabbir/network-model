#include "io/file-write.h"

const std::string io::FileWrite::FOLDER_NAME_RESULTS = "run/results/";
const std::string io::FileWrite::FILE_NAME_TEMPLATE = "run/template/main.tex";
const std::string io::FileWrite::FOLDER_NAME_FIGURES = "figures/";
const std::string io::FileWrite::FOLDER_NAME_OUTPUT = "output";

// REPLACE .TEX extensions with command const string
void io::FileWrite::perform_folder_check_and_clear(
	const std::string& folder_or_result_name
)
{
	const auto& folder_path_root =
		generate_folder_path_root(folder_or_result_name);

	// Clearing and creating results/flow/
	std::filesystem::remove_all(folder_path_root);
	std::filesystem::create_directories(folder_path_root);

	// Create results/flow/output
	const std::string folder_path_for_output =
		generate_folder_path_for_output(folder_or_result_name);
	std::filesystem::create_directories(folder_path_for_output);

	// Create results/flow/output
	const std::string folder_path_output_latex_trash =
		folder_path_root + FOLDER_NAME_OUTPUT;
	std::filesystem::create_directories(folder_path_output_latex_trash);
}


void io::FileWrite::perform_folder_check_and_clear(
	const std::string& folder_or_result_name
)
{
	const std::string folder_path_root =
		generate_folder_path_root(folder_or_result_name);

	std::filesystem::remove_all(folder_path_root);
	std::filesystem::create_directories(folder_path_root);

	const std::string makefile_name = folder_path_root + "Makefile";
	std::ofstream fout_mk(makefile_name);

	fout_mk << "all:" << '\n';
	fout_mk << '\t' << "pdflatex -output-directory= " << FOLDER_NAME_OUTPUT << " " << folder_or_result_name << '\n';
	fout_mk << '\t' << "mv " << FOLDER_NAME_OUTPUT << "/" << FOLDER_NAME_OUTPUT << ".pdf " << folder_or_result_name << ".pdf" << '\n';

	// NEED TO UPDATE LIST FIGURES IN "run/template/main.tex"
	const std::string file_name_main_tex = folder_path_root + folder_or_result_name + ".tex";
	std::filesystem::copy_file(FILE_NAME_TEMPLATE, file_name_main_tex);

	const std::string folder_path_for_output =
		generate_folder_path_for_output(folder_or_result_name);
	std::filesystem::create_directories(folder_path_for_output);

	const std::string folder_path_output_latex_trash =
		folder_path_root + FOLDER_NAME_OUTPUT;
	std::filesystem::create_directories(folder_path_output_latex_trash);
}


std::string io::FileWrite::generate_folder_path_for_output(
	const std::string& folder_or_result_name
)
{
	const auto& root = generate_folder_path_root(folder_or_result_name);
	return root + FOLDER_NAME_FIGURES;
}

std::string io::FileWrite::generate_folder_path_root(
	const std::string& folder_or_result_name
)
{
	return FOLDER_NAME_RESULTS + folder_or_result_name + "/";
}

void io::FileWrite::write_to_particular_folder_in_run(
	const std::vector<str_pair>&
	file_name_and_content_v,
	const std::string& folder_or_result_name
)
{
	perform_folder_check_and_clear(folder_or_result_name);

	const std::string folder_path_output =
		generate_folder_path_for_output(folder_or_result_name);


	for(const auto& [file_name, file_content]: file_name_and_content_v)
	{
		std::ofstream fout(folder_path_output + file_name + ".tex");
		fout << file_content;
	}
}

void io::FileWrite::flow(
	const std::vector<str_pair>& file_name_and_content_v
)
{
	write_to_particular_folder_in_run(file_name_and_content_v, "flow");
}
