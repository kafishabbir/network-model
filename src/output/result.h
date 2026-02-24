#ifndef VISUALIZE_MENU_H
#define VISUALIZE_MENU_H

#include "global/dst.h"
#include "simulate/property.h"
#include "output/property.h"
#include "output-raster/flow.h"
#include "output-vector/flow.h"
#include "utility/str.h"

namespace output
{
	class Result
	{
	
		static inline constexpr auto s = utility::Str::scientific;
		
		static const std::string path_flow;
		static const std::string path_folder_figures;
		
		static std::string generate_file_name_from_index(const int i);
		
	private:
		int count_simulations;
		int count_figures;
		std::stringstream ss_flow;

		std::pair<std::string, std::string>generate_flow_caption(
			const nst::State& state,
			const int count_simulations
		);
		
		std::string plot_flow(
			const nst::State& state,
			const output::Property& visual_property,
			const int count_figures
		);

	public:
		Result();
		~Result();

		void add(
			dst::States& states,
			const simulate::Property& simulate_property,
			const output::Property& visual_property
		);
	};
}


#endif
