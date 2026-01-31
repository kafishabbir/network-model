#ifndef VISUALIZE_FLOW_H
#define VISUALIZE_FLOW_H

#include "visualize/re-scale-state-for-plot.h"

#include <iostream>

namespace visualize
{
	class Flow
	{

		static const bool PLOT_FEATURE_LABEL_NODE_NUMBER;
		static const bool PLOT_FEATURE_LABEL_TUBE_NUMBER;
		static const bool PLOT_FEATURE_LABEL_TUBE_FLOW_RATE;
		static const std::vector<std::string> COLORS;



		static std::string tikz_string_single_plot(
			const State& state
		);

	public:

		static std::vector<std::pair<std::string, std::string>>
			caption_and_code_multiple_plots(
				const States& states
			);
	};


}


#endif
