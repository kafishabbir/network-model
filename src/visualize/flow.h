#ifndef VISUALIZE_FLOW_H
#define VISUALIZE_FLOW_H

#include "visualize/re-scale-state-for-plot.h"
#include "visualize/draw.h"
#include "visualize/flow-verification-label.h"

#include <iostream>

namespace visualize
{
	class Flow
	{
		static std::string tikz_string_single_plot(
			const nst::State& state, const visualize::Property& visual_property
		);

		static std::string label_tube_below(const nst::Tube& tube, const visualize::Property& visual_property);
		static std::string label_tube_middle(const nst::Tube& tube, const int id_tube, const visualize::Property& visual_property);

		static std::string code_tube(const nst::State& state, const int id_tube, const visualize::Property& visual_property);
		static std::string code_node(const nst::Node& node, const int id_node, const visualize::Property& visual_property);

		static std::string code_tubes(const nst::State& state, const visualize::Property& visual_property);
		static std::string code_nodes(const nst::State& state, const visualize::Property& visual_property);

		static std::string code_plot(nst::State& state, const visualize::Property& visual_property);
		static std::string caption_plot(const nst::State& state, const visualize::Property& visual_property);

	public:
		static std::vector<dst::str_pair> caption_and_code_multiple_plots(
			dst::States& states, const visualize::Property& visual_property
		);
	};
}
#endif
