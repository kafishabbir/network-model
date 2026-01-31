#ifndef VISUALIZE_RE_SCALE_STATE_FOR_PLOT_H
#define VISUALIZE_RE_SCALE_STATE_FOR_PLOT_H

#include "global/dst.h"

namespace visualize
{
    class ReScaleStateForPlot
    {
		static const double R_MIN;
		static const double R_MAX;
		static const double LARGEST_ANGLE_A_TUBE_CAN_PROJECT_ON_NODE;
		static const bool PLOT_FEATURE_ACTIVE_DISPLAY_NODE;

		template<class val, class T>
		static std::pair<val, val> min_max(
			const std::vector<T>& v,
			val T::*member
		);

		static double calculate_tube_displacement_due_to_node(
			const double r_node,
			const double r_tube
		);

		//sets x_max - x_min = 1
		static void node_coordinates(State& state);

		//length from node positions
		static void tube_lengths(State& state);

		//radius scaled to R_MIN R_MAX
		static void tube_radius(State& state);

		//a circular node sets the tubes radially further
		static void node_radius(State& state);

		//makes mpos long format, if needed, displaces to make space for node
		static void mpos(State& state);

        public:

        static State create_state_visual(const State& state);
    };
}

#endif
