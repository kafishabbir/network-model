#ifndef VISUALIZE_MENU_H
#define VISUALIZE_MENU_H

#include "dst/system.h"
#include "output/property.h"
#include "utility/str.h"
#include "output/json.h"

namespace output
{
	class Result
	{
	
		static inline constexpr auto s = utility::Str::scientific;
		
		static const std::string path_flow;
		static const std::string path_folder_figures;
		static const std::string path_raw;
		static const std::string file_name_full_raw;
		
		static std::string generate_file_name_from_index(const int i);
		
	private:
		int count_simulations;
		int count_figures;
		Json json;
		std::stringstream ss_flow;
		
		
		std::string generate_flow_caption(
			const dst::State& state,
			const int count_simulations
		);
		
		
		std::string generate_flow_page_text(
			const dst::State& state,
			const int count_simulations
		);
		
		
		std::string save_figure_and_generate_inclusion_code(
			const dst::State& state,
			const output::Property& visual_property,
			const std::string& file_name
		);
		
		
		std::string plot_flow(
			const dst::State& state,
			const output::Property& visual_property,
			const int count_figures
		);
		
	public:
		Result();
		~Result();

		void add(
			dst::System& system,
			const output::Property& visual_property
		);
	};
}

#endif
