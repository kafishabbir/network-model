#include "visualize/flow-file-out.h"

const std::string visualize::FlowFileOut::FOLDER_RUN_FLOW = "run/flow/";
const std::string visualize::FlowFileOut::FOLDER_FIGURES = "figures/";
const std::string visualize::FlowFileOut::FILE_TEX_LIST_FIGURES = "listfigures.tex";
const std::string visualize::FlowFileOut::FILE_TEX_FIGURE_PART_NAME = "fig-";
const std::string visualize::FlowFileOut::XX_FILE_TEX_EXTENSION = ".tex";

visualize::FlowFileOut::FlowFileOut(const int figure_index):
	figure_index(figure_index)
{}

std::string visualize::FlowFileOut::file_list_figures()
{
	return FOLDER_RUN_FLOW + FILE_TEX_LIST_FIGURES;
}

std::string visualize::FlowFileOut::file_name() const
{
	std::stringstream ss;
	ss << FILE_TEX_FIGURE_PART_NAME << 101 + figure_index;
	return ss.str();
}

std::string visualize::FlowFileOut::file_name_with_tex_extension() const
{
	return file_name() + XX_FILE_TEX_EXTENSION;
}

std::string visualize::FlowFileOut::path() const
{
	return FOLDER_RUN_FLOW + FOLDER_FIGURES + file_name_with_tex_extension();
}

std::string visualize::FlowFileOut::path_for_latex_input() const
{
	return FOLDER_FIGURES + file_name();
}




