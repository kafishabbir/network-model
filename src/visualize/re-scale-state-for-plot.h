#ifndef VISUALIZE_RE_SCALE_STATE_FOR_PLOT_H
#define VISUALIZE_RE_SCALE_STATE_FOR_PLOT_H

#include "global/dst.h"
#include <iostream>
#include "global/decl.h"

namespace visualize
{
    class ReScaleStateForPlot
    {
		template<class val, class T>
		static std::pair<val, val> min_max(
			const std::vector<T>& v,
			val T::*member
		);

		template<class val, class T, class U>
		static std::pair<val, val> min_max(
			const std::vector<T>& v,
			U T::*member,
			val U::*submember
		);

		static double calculate_tube_visual_displacement_due_to_node(
			const double r_node,
			const double r_tube
		);

		//sets x_max - x_min = 1
		static void node_coordinates(nst::State& state);

		//length from node positions
		static void tube_lengths(nst::State& state);

		//radius scaled to decl::nps_latex_plot::nps_flow::nps_parameters::tube_radius_min decl::nps_latex_plot::nps_flow::nps_parameters::tube_radius_max
		static void tube_radius(nst::State& state);

		//a circular node sets the tubes radially further
		static void node_radius(nst::State& state);

		//makes mpos long format, if needed, displaces to make space for node
		static void mpos(nst::State& state);

        public:

        static void add_state_visual(nst::State& state);
    };
}

#endif
