#ifndef VISUALIZE_FLOW_H
#define VISUALIZE_FLOW_H

#include "global/dst.h"
#include "visualize/draw-shapes.h"
#include "visualize/flow-file-out.h"

#include <fstream>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace visualize
{
	class Flow
	{
		static const double R_MIN;
		static const double R_MAX;
		static const double LARGEST_ANGLE_A_TUBE_CAN_PROJECT_ON_NODE;
		static const bool PLOT_FEATURE_ACTIVE_DISPLAY_NODE;
		static const bool PLOT_FEATURE_LABEL_NODE_NUMBER;
		static const bool PLOT_FEATURE_LABEL_TUBE_NUMBER;
		static const bool PLOT_FEATURE_LABEL_TUBE_FLOW_RATE;
		static const std::vector<std::string> COLORS;

		static std::pair<double, double> radius_min_max(
			const Tubes& tubes
		);
		static double length_min(const Tubes& tubes);

		// flow.h
		static double calculate_tube_displacement_due_to_node(
			const double r_node,
			const double r_tube
		);

		// flow.h
		static Nodes scale_coordinates_to_unit_scale(Nodes v);

		// flow.h
		static Tubes scale_mpos_long(Tubes tubes, const Nodes& nodes);

		// flow.h
		static Tubes scale_radius(Tubes tubes);

		// flow.h
		static Tubes scale_set_tube_length_to_visual_length(
			Tubes tubes,
			const Nodes& nodes
		);



		// flow.h
		static Nodes assign_radius_to_each_node(
			Nodes nodes,
			const Tubes& tubes
		);

		// flow.h
		static std::string tikz_string_single_plot(
			const State& state
		);

	public:

		static void mpos_multiple_plots_in_1_pdf(
			const States& states
		);
	};


}


#endif
