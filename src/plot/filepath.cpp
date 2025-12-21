#include "plot/filepath.h"

const std::string plot::FilePath::FOLDER_RUN_FLOW = "run/flow/";
const std::string plot::FilePath::FOLDER_FIGURES = "figures/";
const std::string plot::FilePath::FILE_TEX_LIST_FIGURES = "listfigures.tex";
const std::string plot::FilePath::FILE_TEX_FIGURE_PART_NAME = "fig-";
const std::string plot::FilePath::XX_FILE_TEX_EXTENSION = ".tex";

plot::FilePath::FilePath(const int figure_index):
	figure_index(figure_index)
{}

std::string plot::FilePath::file_list_figures()
{
	return FOLDER_RUN_FLOW + FILE_TEX_LIST_FIGURES;
}
std::string plot::FilePath::path_for_io_and_exe() const
{
	return FOLDER_RUN_FLOW + FOLDER_FIGURES + file_name_with_tex();
}

std::string plot::FilePath::path_for_latex() const
{
	return FOLDER_FIGURES + file_name_without_tex();
}

std::string plot::FilePath::file_name_without_tex() const
{
	std::stringstream ss;
	ss << FILE_TEX_FIGURE_PART_NAME << 101 + figure_index;
	return ss.str();
}

std::string plot::FilePath::file_name_with_tex() const
{
	return file_name_without_tex() + XX_FILE_TEX_EXTENSION;
}
