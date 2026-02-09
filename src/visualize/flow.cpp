#include "visualize/flow.h"

std::string visualize::Flow::code_node(const nst::Node& node, const int node_id, const visualize::Property& visual_property)
{
	const double x = node.visual.x;
	const double y = node.visual.y;
	const double radius = node.visual.radius;
	std::stringstream ss;

	if(visual_property.draw_node_perimeter)
	{
		ss << visualize::Draw::circle(x, y, radius) << '\n';
	}
	return ss.str();
}


std::string visualize::Flow::code_node_label(const nst::Node& node, const int node_id, const visualize::Property& visual_property)
{
	const double x = node.visual.x;
	const double y = node.visual.y;
	//const double radius = node.visual.radius;
	std::stringstream ss;

	if(visual_property.label_node_id)
	{
		std::stringstream ss_node;
		ss_node << "$\\nu_{" << node_id << "}$";
		ss << visualize::Draw::node(x, y, ss_node.str()) << '\n';
	}
	if(visual_property.label_node_pressure)
	{
		std::stringstream ss_pressure;
		ss_pressure << "$p=" << visualize::Draw::num(node.pressure) << "$";
		ss << visualize::Draw::node(x, y + 0.01, ss_pressure.str()) << '\n';
	}
	return ss.str();
}


std::string visualize::Flow::label_tube_above(const nst::Tube& tube, const visualize::Property& visual_property)
{
	const double x_proportion_location = 0.3;
	const double rv = tube.visual.radius;
	const double lv = tube.visual.length;

	std::stringstream ss;
	if(visual_property.label_tube_direction)
	{
		ss << "(" << tube.id_node_first << "-" << tube.id_node_second << "), ";
	}
	if(visual_property.label_tube_radius)
	{
		ss << "$r=" << visualize::Draw::num(tube.radius) << "$, ";
	}
	if(visual_property.label_tube_length)
	{
		ss << "$l=" << visualize::Draw::num(tube.length) << "$, ";
	}

	return visualize::Draw::node(
		lv * x_proportion_location,
		2 * rv,
		ss.str()
	);
}

std::string visualize::Flow::label_tube_middle(const nst::Tube& tube, const int tube_id, const visualize::Property& visual_property)
{
	const double lv = tube.visual.length;
	std::stringstream ss;

	if(visual_property.label_tube_id)
	{
		ss << "$b_{" << tube_id << "}$";
	}

	return visualize::Draw::node(
		lv / 2,
		0,
		ss.str()
	);
}

std::string visualize::Flow::label_tube_below(const nst::Tube& tube, const visualize::Property& visual_property)
{
	const double rv = tube.visual.radius;
	const double lv = tube.visual.length;

	std::stringstream ss;

	int i = tube.id_node_first;
	int j = tube.id_node_second;

	double q = tube.calculated.flow_rate;
	double arrow_begin = lv/8;
	double arrow_end = lv*3/8;
	double q_pos = lv*3/8;
	if(q < 0)
	{
		std::swap(i, j);
		arrow_begin = lv*7/8;
		arrow_end = lv*5/8;
		q = std::abs(q);
		q_pos = lv*5/8;
	}

	if(visual_property.label_tube_flow_rate)
	{
		ss << visualize::Draw::arrow(arrow_begin, arrow_end, -1.75 * rv) << '\n';

		std::stringstream ss_node;
		ss_node << "$" << "q_{" << i << j << "}=" << visualize::Draw::num(q) << "$";

		ss << visualize::Draw::node(q_pos, - 2 * rv, ss_node.str());
	}

	return ss.str();
}


std::string visualize::Flow::code_tube(const nst::State& state, const int tube_id, const visualize::Property& visual_property)
{
	const auto& tube = state.tubes[tube_id];
	const auto& node_first = state.nodes[tube.id_node_first];
	const auto& node_second = state.nodes[tube.id_node_second];
	/*
	std::cout << "tube_id=" << tube_id << "\n";
	std::cout << "radius=" << tube.radius << "\n";
	std::cout << "length=" << tube.radius << "\n";
	std::cout << "mpos={";
	for(auto x: tube.mpos)
	{
		std::cout << x << ", ";
	}
	std::cout << "}\n";

	std::cout << "visual.radius=" << tube.visual.radius << "\n";
	std::cout << "visual.length=" << tube.visual.length << "\n";
	std::cout << "visual.visual.mpos={";
	for(auto x: tube.visual.mpos)
	{
		std::cout << x << ", ";
	}
	std::cout << "}\n";
	std::cout << "calculated.flow_rate=" << tube.calculated.flow_rate << "\n";
	std::cout << "\n";
	*/
	std::stringstream ss;
	ss << visualize::Draw::mpos_horizontal_rectangles(tube, visual_property.colors_str_v);

	// length, radius
	ss << label_tube_above(tube, visual_property) << '\n';

	// tube id
	ss << label_tube_middle(tube, tube_id, visual_property) << '\n';

	// flow rate
	ss << label_tube_below(tube, visual_property) << '\n';

	return visualize::Latex::scope_shift_and_rotate(
		node_first.visual.x,
		node_first.visual.y,
		node_first.visual.relative_angle(node_second),
		ss.str()
	);
}

std::string visualize::Flow::code_nodes(const nst::State& state, const visualize::Property& visual_property)
{
	const auto& nodes = state.nodes;
	const int n_nodes = nodes.size();
	std::stringstream ss;
	for(int i = 0; i < n_nodes; ++ i)
	{
		ss << code_node(nodes[i], i, visual_property) << '\n';
	}

	return ss.str();
}

std::string visualize::Flow::code_nodes_labels(const nst::State& state, const visualize::Property& visual_property)
{
	const auto& nodes = state.nodes;
	const int n_nodes = nodes.size();
	std::stringstream ss;
	for(int i = 0; i < n_nodes; ++ i)
	{
		ss << code_node_label(nodes[i], i, visual_property) << '\n';
	}

	return ss.str();
}

std::string visualize::Flow::code_tubes(const nst::State& state, const visualize::Property& visual_property)
{
	const auto& tubes = state.tubes;
	const int n_tubes = tubes.size();
	std::stringstream ss;
	for(int i = 0; i < n_tubes; ++ i)
	{
		ss << code_tube(state, i, visual_property) << '\n';
	}

	return ss.str();
}


std::string visualize::Flow::code_plot(nst::State& state, const visualize::Property& visual_property)
{
	visualize::ReScaleStateForPlot::add_state_visual(state, visual_property);

	std::stringstream ss;

	ss << code_nodes(state, visual_property) << '\n';
	ss << code_tubes(state, visual_property) << '\n';
	ss << code_nodes_labels(state, visual_property) << '\n';
	return visualize::Latex::scope_tikzpicture(ss.str());
}

std::string visualize::Flow::caption_plot(const nst::State& state, const visualize::Property& visual_property)
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

std::vector<dst::str_pair> visualize::Flow::caption_and_code_multiple_plots(
	dst::States& states, const visualize::Property& visual_property
)
{
	const int n_plots = states.size();
	std::vector<dst::str_pair> caption_and_code_v(n_plots);
	for(int i = 0; i < n_plots; ++ i)
	{
		auto& state = states[i];
		caption_and_code_v[i] = {caption_plot(state, visual_property), code_plot(state, visual_property)};
	}
	return caption_and_code_v;
}
