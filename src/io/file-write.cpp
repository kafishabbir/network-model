#include "io/file-write.h"

std::string io::FileWrite::generate_folder_path_figures(
	const std::string& folder_or_result_name
)
{
	const auto& folder_path_root = generate_folder_path_root(folder_or_result_name);
	return folder_path_root + decl::nps_latex_plot::nps_folder::figures;
}

std::string io::FileWrite::generate_folder_path_root(
	const std::string& folder_or_result_name
)
{
	return decl::nps_latex_plot::nps_folder::results + folder_or_result_name + "/";
}

// REPLACE .TEX extensions with command const string
void io::FileWrite::clear_result_and_generate_folders(
	const std::string& folder_or_result_name
)
{
	const std::string folder_path_root =
		generate_folder_path_root(folder_or_result_name);
	const std::string folder_path_figures =
		generate_folder_path_figures(folder_or_result_name);
	const std::string folder_path_output =
		folder_path_root + decl::nps_latex_plot::nps_folder::output;

	// Clear and Create results/flow/figures
	std::filesystem::remove_all(folder_path_figures);
	std::filesystem::create_directories(folder_path_figures);

	// Create results/flow/output
	std::filesystem::create_directories(folder_path_output);
}

std::string io::FileWrite::makefile_text(
	const std::string& folder_or_result_name
)
{
	std::stringstream ss;

	ss << "all:" << '\n';
	ss << '\t' << "pdflatex -output-directory=" << decl::nps_latex_plot::nps_folder::output << " " << folder_or_result_name << '\n';
	ss << '\t' << "mv " << decl::nps_latex_plot::nps_folder::output << "/" << folder_or_result_name << ".pdf " << folder_or_result_name << ".pdf" << '\n';

	return ss.str();
}


std::string io::FileWrite::main_tex_text(
	const std::string& file_name_list_figures
)
{
	const std::string& file_name = decl::nps_latex_plot::nps_folder::figures + file_name_list_figures;
	std::ifstream fin(decl::nps_latex_plot::nps_file::template_main);

	std::stringstream ss;

	ss << fin.rdbuf() << '\n';
	ss << visualize::Latex::begin_end_document_scope(file_name);

	return ss.str();
}

void io::FileWrite::create_makefile_and_main_tex(
	const std::string& folder_or_result_name,
	const std::string& file_name_list_figures
)
{
	const std::string& folder_path_root = generate_folder_path_root(folder_or_result_name);
	const std::string& file_name_makefile = folder_path_root + "Makefile";
	const std::string& file_name_main_tex = folder_path_root + folder_or_result_name + ".tex";

	std::ofstream fout_mk(file_name_makefile);
	fout_mk << makefile_text(folder_or_result_name);

	std::ofstream fout_main(file_name_main_tex);
	fout_main << main_tex_text(file_name_list_figures);
}

void io::FileWrite::write_to_particular_folder_in_run(
	const std::vector<dst::str_pair>& file_name_and_content_v,
	const std::string& folder_or_result_name
)
{
	clear_result_and_generate_folders(folder_or_result_name);
	create_makefile_and_main_tex(
		folder_or_result_name,
		file_name_and_content_v.front().first
	);

	const std::string folder_path_figures =
		generate_folder_path_figures(folder_or_result_name);

	for(const auto& [file_name_part, file_content]: file_name_and_content_v)
	{
		const std::string& file_name_tex = folder_path_figures + file_name_part + ".tex";
		std::ofstream fout(file_name_tex);
		fout << file_content;
	}
}

void io::FileWrite::flow(
	const std::vector<dst::str_pair>& file_name_and_content_v
)
{
	write_to_particular_folder_in_run(file_name_and_content_v, "flow");
}
