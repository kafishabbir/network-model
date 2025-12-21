#ifndef PLOT_FLOW_H
#define PLOT_FLOW_H

#include "global/dst.h"
#include "plot/latexcode.h"
#include "plot/filepath.h"

#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace plot
{
	class Flow
	{
		class FilePath;
		static const double R_MIN;
		static const double R_MAX;
		static const double LARGEST_ANGLE_A_TUBE_CAN_PROJECT_ON_NODE;
		static const bool PLOT_FEATURE_ACTIVE_DISPLAY_NODE;
		static const std::vector<std::string> COLORS;

		static std::pair<double, double> radius_min_max(
			const Tubes& v_tubes
		);
		static double length_min(const Tubes& v_tubes);

		static double calculate_tube_displacement_due_to_node(
			const double r_node,
			const double r_tube
		);

		static Nodes scale_coordinates_to_unit_scale(Nodes v);


		static Tubes scale_mpos_long(Tubes v_tubes, const Nodes& v_nodes);

		static Tubes scale_radius(Tubes v_tubes);
		static Tubes scale_set_tube_length_to_visual_length(
			Tubes v_tubes,
			const Nodes& v_nodes
		);

		static std::string tikz_string_rectangles_mpos_horizontal(
			const nst::Tube& tube
		);

		static std::string tikz_string_single_plot(
			Nodes v_nodes,
			Tubes v_tubes
		);

		static Nodes assign_radius_to_each_node(
			Nodes v_nodes,
			const Tubes& v_tubes
		);

	public:

		static void mpos_multiple_plots_in_1_pdf(
			const std::vector<std::pair<Nodes,Tubes>>& v_plots
		);
	};


}


#endif
