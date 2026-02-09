#ifndef GLOBAL_DECL_H
#define GLOBAL_DECL_H

#include <string>
#include <cmath>
#include <vector>

namespace decl
{
	const double pi = std::acos(-1);
	namespace nps_latex_plot
	{
		namespace nps_file
		{
			// figure_initial
			const std::string figure_initial = "figure-";
			// list_figures
			const std::string list_figures = "list-figures";
			// template_main
			const std::string template_main = "template/main.tex";
		}
		namespace nps_folder
		{
			// results
			const std::string results = "run/results/";
			// figures
			const std::string figures = "figures/";
			// output
			const std::string output = "output";
		}
		namespace nps_flow
		{
			// colors_str_v
			const std::vector<std::string> colors_str_v{"cw", "cnw"};
			namespace nps_parameters
			{
				// tube_radius_min
				const double tube_radius_min = 0.02;
				// tube_radius_max
				const double tube_radius_max = 0.10;
				// largest_angle_tube_project_on_node
				const double largest_angle_tube_project_on_node = pi / 2.0;
			}
			namespace nps_feature
			{
				// draw_node_perimeter
				const bool draw_node_perimeter = true;
			}
			namespace nps_label
			{
				// node_id
				const bool node_id = true;
				// node_pressure
				const bool node_pressure = true;
				// tube_id
				const bool tube_id = true;
				// tube_radius
				const bool tube_radius = true;
				// tube_length
				const bool tube_length = true;
				// tube_flow_rate
				const bool tube_flow_rate = true;
			}
		}
	}
}

#endif
