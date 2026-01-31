#include "visualize/flow.h"

const std::vector<std::string> visualize::Flow::COLORS{"cw", "cnw"};

const bool visualize::Flow::PLOT_FEATURE_LABEL_NODE_NUMBER = true;
const bool visualize::Flow::PLOT_FEATURE_LABEL_TUBE_NUMBER = true;
const bool visualize::Flow::PLOT_FEATURE_LABEL_TUBE_FLOW_RATE = true;


std::string code_node(const nst::Node& node, const int node_id)
{
	const double x = node.visual.x;
	const double y = node.visual.y;
	const double radius = node.visual.radius;
	std::stringstream ss;

	if(PLOT_FEATURE_DRAW_NODE)
	{
		ss << visualize::Draw::circle(x, y, radius) << '\n';
	}
	if(PLOT_FEATURE_LABEL_NODE_NUMBER)
	{
		ss_node << "$\\nu_{" << node_id << "}$";
		ss << visualize::DrawShapes::node(x, y, ss_node.str()) << '\n';
	}
	if(PLOT_FEATURE_LABEL_NODE_PRESSURE)
	{
		std::stringstream ss_pressure;
		ss_pressure << "$p=" << visualize::Draw::num(node.pressure) << "$";
		ss << visualize::DrawShapes::node(x + 1.2 * radius, y, ss_pressure.str()) << '\n';
	}
	return ss.str();
}

std::string visualize::Flow::label_tube_above(const nst::Tube& tube)
{
	const double x_proportion_location = 0.3;
	const double rv = tube.visual.radius;
	const double lv = tube.visual.length;

	std::stringstream ss;
	if(PLOT_FEATURE_LABEL_TUBE_RADIUS)
	{
		ss << "$r=" << visualize::Draw::num(tube.radius) << "$, ";
	}
	if(PLOT_FEATURE_LABEL_TUBE_LENGTH)
	{
		ss << "$l=" << visualize::Draw::num(tube.length) << "$, ";
	}

	return visualize::Draw::node(
		lv * x_proportion_location,
		2 * rv,
		ss.str()
	);
}

std::string visualize::Flow::label_tube_middle(const nst::Tube& tube, const int tube_id)
{
	const double lv = tube.visual.length;
	std::stringstream ss;

	if(PLOT_FEATURE_LABEL_TUBE_NUMBER)
	{
		ss << "$b_" << tube_id << "$";
	}

	return visualize::Draw::node(
		lv / 2,
		0,
		ss.str()
	);
}

std::string visualize::Flow::label_tube_below(const nst::Tube& tube)
{
	const double rv = tube.visual.radius;
	const double lv = tube.visual.length;

	std::stringstream ss;

	int i = tube.id_node_first;
	int j = tube.id_node_second;

	double q = tube.flow_rate;
	double arrow_begin = lv/8;
	double arrow_end = lv*3/8;
	if(q < 0)
	{
		std::swap(i, j);
		arrow_begin = lv*7/8;
		arrow_end = lv*5/8;
		q = std::abs(q);
	}

	if(PLOT_FEATURE_LABEL_TUBE_FLOW_RATE)
	{
		ss << visualize::Draw::arrow(arrow_begin, arrow_end, -1.75 * rv) << '\n';

		std::stringstream ss_node;
		ss_node << "$" << "q_{" << i << j << "}=" << visualize::Draw::num(q) << "$";

		ss << visualize::Draw::node(lv / 2, - 2 * rv, ss_node.str());
	}

	return ss.str();
}


std::string visualize::Flow::code_tube(const State& state, const int tube_id)
{
	const auto& tube = state.tubes[tube_id];
	const auto& node_first = state.nodes[tube.id_node_first];
	const auto& node_second = state.nodes[tube.id_node_second];

	std::stringstream ss;
	ss << visualize::Draw::mpos_horizontal_rectangles(tube, COLORS);

	// length, radius
	ss << label_tube_above(tube) << '\n';

	// tube id
	ss << label_tube_middle(tube, tube_id) << '\n';

	// flow rate
	ss << label_tube_below(tube) << '\n';

	return visualize::Draw::scope(
		node_first.x,
		node_first.y,
		node_first.relative_angle(node_second),
		ss.str()
	);
}

std::sttring visualize::Flow::code_nodes(const State& state)
{
	const auto& nodes = state.nodes;
	const int n = n_nodes;
	std::stringstream ss;
	for(int i = 0; i < n_nodes; ++ i)
	{
		ss << code_node(nodes[i], i) << '\n';
	}

	return ss.str();
}

std::sttring visualize::Flow::code_tubes(const State& state)
{
	const auto& tubes = state_visual.tubes;
	const int n_tubes = tubes.size();
	std::stringstream ss;
	for(int i = 0; i < n_tubes; ++ i)
	{
		ss << code_tube(state, i) << '\n';
	}

	return ss.str();
}


std::string visualize::Flow::code_plot(const State& state)
{
	const auto state_visual =
		visualize::ReScaleStateForPlot::create_state_visual(state);

	std::stringstream ss;

	ss << code_nodes(state_visual) << '\n';
	ss << code_tubes(state_visual) << '\n';

	return visualize::Draw::scope_tikzpicture(ss.str());;
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
		caption_and_code_v[i] = {caption_plot(state), code_plot(state)};
	}
	return caption_and_code_v;
}
