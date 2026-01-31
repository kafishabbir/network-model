#include "visualize/flow.h"

const std::vector<std::string> visualize::Flow::COLORS{"cw", "cnw"};

const bool visualize::Flow::PLOT_FEATURE_LABEL_NODE_NUMBER = true;
const bool visualize::Flow::PLOT_FEATURE_LABEL_TUBE_NUMBER = true;
const bool visualize::Flow::PLOT_FEATURE_LABEL_TUBE_FLOW_RATE = true;


std::string flow_rate_information(const nst::Tube& tube, const nst::Tube& tube_visual)
{
	const int i = tube.id_node_first;
	const int j = tube.id_node_second;
	const double r = tube.radius;
	const double l = tube.length;
	const double q = tube.flow_rate;
	std::stringstream ss, ss_q, ss_rl;
	ss_q << "$" << "q_{" << i << j << "}=" << q << "$";
	ss_rl << "$r=" << r << "$, $l=" << l << "$";

	const double rv = tube_visual.radius;
	const double lv = tube_visual.length;

	double arrow_begin = lv/8;
	double arrow_end = lv*3/8;
	if(q<0)
	{
		arrow_begin = lv*7/8;
		arrow_end = lv*5/8;
	}
	ss << "\\draw[->] (" << arrow_begin << ", " << -1.75 * rv << ") -- (" << arrow_end << ", " << -1.75 * rv << ");";

	ss << visualize::DrawShapes::node(lv / 2, -2 * rv, ss_q.str()) << "\n";
	ss << visualize::DrawShapes::node(lv / 2, 2 * rv, ss_rl.str()) << "\n";
	return ss.str();
}


std::string visualize::Flow::code_plot(const State& state)
{
	const auto state_visual =
		visualize::ReScaleStateForPlot::create_state_visual(state);

	std::stringstream ss;


}

std::string visualize::Flow::caption_plot(const State& state)
{
	const int n_nodes = state.nodes.size();
	const int n_tubes = state.tubes.size();
	const double mu_1 = state.mu1;
	const double mu_2 = state.mu2;
	const double sigma = state.sigma;

	std::stringstream ss;
	ss << "$n_{nodes}="	<< n_nodes	<< "$" << ", ";
	ss << "$n_{tubes}="	<< n_tubes	<< "$" << ", ";
	ss << "$\\mu_{1}="	<< mu_1		<< "$" << ", ";
	ss << "$\\mu_{2}="	<< mu_2		<< "$" << ", ";
	ss << "$\\sigma="	<< sigma	<< "$" << ".";

	return ss.str();
}

std::pair<std::string, std::string>
visualize::Flow::caption_and_code_single_plot
(
	const State& state
)
{
	return {caption_plot(state), code_plot(state)};
}

std::vector<std::pair<std::string, std::string>>
visualize::Flow::caption_and_code_multiple_plots(
	const States& states
)
{
	const int n_plots = states.size();
	std::vector<std::pair<std::string, std::string>> caption_and_code_v(n_plots);
	for(int i = 0; i < n_plots; ++ i)
	{
		const auto& state = states[i];
		caption_and_code_v[i] = caption_and_code_single_plot(state);
	}
	return caption_and_code_v;
}
