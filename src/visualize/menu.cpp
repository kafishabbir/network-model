#include "visualize/menu.h"

void visualize::Menu::append(const std::vector<dst::str_pair>& caption_and_code_new_v)
{
	auto& parent = caption_and_code_v;
	const auto& child = caption_and_code_new_v;

	parent.insert(parent.end(), child.cbegin(), child.cend());
}

void visualize::Menu::flow(dst::States& states, const visualize::Property& visual_property)
{
	append(visualize::Flow::caption_and_code_multiple_plots(states, visual_property));
}

std::string visualize::Menu::generate_file_name_from_index(const int i)
{
	std::stringstream ss;
	ss << decl::nps_latex_plot::nps_file::figure_initial << 1001 + i;
	return ss.str();
}

std::vector<dst::str_pair> visualize::Menu::out() const
{
	const int n_files = caption_and_code_v.size();

	std::stringstream ss;
	std::vector<dst::str_pair> file_name_and_file_content_v(n_files + 1);

	for(int i = 0; i < n_files; ++ i)
	{
		const auto& [caption, file_content] = caption_and_code_v[i];
		const auto& file_name = generate_file_name_from_index(i);

		file_name_and_file_content_v[i + 1] = {file_name, file_content};

		const auto& begin_end_figure_code =
			visualize::Latex::begin_end_figure_scope(decl::nps_latex_plot::nps_folder::figures + file_name, caption);
		ss << begin_end_figure_code << '\n';
	}

	file_name_and_file_content_v.front() = {decl::nps_latex_plot::nps_file::list_figures, ss.str()};

	return file_name_and_file_content_v;
}
