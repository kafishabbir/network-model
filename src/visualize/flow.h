#ifndef VISUALIZE_FLOW_H
#define VISUALIZE_FLOW_H

#include "visualize/re-scale-state-for-plot.h"
#include "visualize/draw.h"
#include "visualize/latex.h"

#include <iostream>
#include "global/decl.h"

namespace visualize
{
	class Flow
	{
		static std::string tikz_string_single_plot(
			const nst::State& state
		);

		static std::string code_node(const nst::Node& node, const int node_id);
		static std::string code_node_label(const nst::Node& node, const int node_id);
		static std::string label_tube_above(const nst::Tube& tube);
		static std::string label_tube_middle(const nst::Tube& tube, const int tube_id);
		static std::string label_tube_below(const nst::Tube& tube);
		static std::string code_tube(const nst::State& state, const int tube_id);
		static std::string code_nodes(const nst::State& state);
		static std::string code_nodes_labels(const nst::State& state);
		static std::string code_tubes(const nst::State& state);
		static std::string code_plot(nst::State& state);
		static std::string caption_plot(const nst::State& state);

	public:
		static std::vector<dst::str_pair> caption_and_code_multiple_plots(
			dst::States& states
		);
	};
}
#endif
