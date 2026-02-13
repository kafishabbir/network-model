#ifndef VISUALIZE_RE_SCALE_STATE_FOR_PLOT_H
#define VISUALIZE_RE_SCALE_STATE_FOR_PLOT_H

#include "visualize/property.h"

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
			const double r_tube,
			const visualize::Property& visual_property
		);

		//sets x_max - x_min = 1
		static void node_coordinates(nst::State& state, const visualize::Property& visual_property);

		//length from node positions
		static void tube_lengths(nst::State& state, const visualize::Property& visual_property);

		//radius scaled to visual_property.tube_radius_min visual_property.tube_radius_max
		static void tube_radius(nst::State& state, const visualize::Property& visual_property);

		//a circular node sets the tubes radially further
		static void node_radius(nst::State& state, const visualize::Property& visual_property);

		//makes mpos long format, if needed, displaces to make space for node
		static void mpos(nst::State& state, const visualize::Property& visual_property);

		static std::vector<double> mpos_long_displaced_scaled(
			const nst::Tube& tube,
			const double p1,
			const double p2
		);

        public:

        static void add_state_visual(nst::State& state, const visualize::Property& visual_property);
    };
}

#endif
