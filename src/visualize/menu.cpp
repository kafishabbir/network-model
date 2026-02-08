#include "visualize/menu.h"
const std::string visualize::Menu::FILE_NAME_INITIAL = "figure-";
const std::string visualize::Menu::FILE_NAME_LIST_FIGURES = "list-figures";

void append(
	const std::vector<std::pair<std::string, std::string>>&
	caption_and_code_new_v
)
{
	auto& parent = caption_and_code_v;
	const auto& child = caption_and_code_new_v;

	parent.insert(parent.end(), child.cbegin(), child.cend());
}

void visualize::Menu::flow(
	const States& states
)
{
	append(
		visualize::Flow::caption_and_code_multiple_plots(states)
	);
}

std::string generate_file_name_from_index(const int i)
{
	std::stringstream ss;
	ss << FILE_NAME_INITIAL << 1000 + i;
	return ss.str();
}

std::vector<std::pair<std::string, std::string>>
visualize::Menu::out() const
{
	const int n_files = caption_and_code_v.size();

	std::stringstream ss;
	std::vector<std::pair<std::string, std::string>>
	file_name_and_file_content_v(n_files + 1);

	for(int i = 0; i < n_files; ++ i)
	{
		const auto& [caption, file_content] = caption_and_code_v[i];
		const auto& file_name = generate_file_name_from_index(i);

		file_name_and_file_content_v[i + 1] = {file_name, file_content};

		const auto& begin_end_figure_code =
			visualize::Latex::begin_end_figure_scope(file_name, caption);
		ss << begin_end_figure_code << '\n';
	}

	file_name_and_file_content_v.front() = {FILE_NAME_LIST_FIGURES, ss.str()};

	return file_name_and_file_content_v;
}
