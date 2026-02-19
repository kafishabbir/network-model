#include "visualize/flow.h"

std::string visualize::Flow::code_node(const nst::Node& node, const int id_node, const visualize::Property& visual_property)
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

std::string visualize::Flow::label_tube_middle(const nst::Tube& tube, const int id_tube, const visualize::Property& visual_property)
{
	const double lv = tube.visual.length;
	std::stringstream ss;

	if(visual_property.label_id_tube)
	{
		ss << "$b_{" << id_tube << "}$";
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
		ss_node << "$" << "q_{" << i << j << "}=" << Draw::num(q) << "$";

		ss << visualize::Draw::node(q_pos, - 2 * rv, ss_node.str());
	}

	return ss.str();
}


std::string visualize::Flow::code_tube(const nst::State& state, const int id_tube, const visualize::Property& visual_property)
{
	const auto& tube = state.tubes[id_tube];
	const auto& node_first = state.nodes[tube.id_node_first];
	const auto& node_second = state.nodes[tube.id_node_second];

	std::stringstream ss;
	ss << visualize::Draw::mpos_horizontal_rectangles(tube, visual_property.colors_str_v);

	ss << label_tube_below(tube, visual_property) << '\n';
	ss << label_tube_middle(tube, id_tube, visual_property) << '\n';

	return visualize::Draw::scope_shift_and_rotate(
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

	ss << FlowVerificationLabel::code_tubes_labels(state, visual_property) << '\n';
	ss << FlowVerificationLabel::code_nodes_labels(state, visual_property) << '\n';

	return visualize::Latex::scope_tikzpicture(ss.str());
}


std::string visualize::Flow::caption_plot(const nst::State& state, const visualize::Property& visual_property)
{
	const std::string comment = state.reference.comment;
	const int id_step = state.reference.id_step;

	const double time_elapsed = state.measured.time_elapsed;
	const auto total_fluid_added = state.measured.total_fluid_added;
	const auto total_fluid_evacuated = state.measured.total_fluid_evacuated;
	const auto saturation = state.calculated.saturation;

	const auto volume_total_delta = state.calculated.volume_total_delta * 100;
	const auto water_volume_delta  = state.calculated.water_volume_delta * 100;
	const auto oil_volume_delta  = state.calculated.oil_volume_delta * 100;

	const double time_step = state.calculated.time_step;
	const auto fluid_added = state.calculated.fluid_added;
	const auto fluid_evacuated = state.calculated.fluid_evacuated;


	const int n_nodes = state.nodes.size();
	const int n_tubes = state.tubes.size();
	const double sigma = state.physical_constant.sigma;
	const double mu_1 = state.water_viscosity();
	const double mu_2 = state.oil_viscosity();

	const double time_step_resolution = state.simulation_constant.time_step_resolution;

	std::stringstream ss;
	ss << comment << ", ";
	ss << "step-id=" << id_step << ", ";
	ss << "$S=" << Draw::num(saturation) << "$, ";
	ss << "time-elapsed=$" << Draw::num(time_elapsed) << "$" << ", ";
	ss << "t-fluid-added=" << Draw::str(total_fluid_added) << ", ";
	ss << "t-fluid-evacuated=" << Draw::str(total_fluid_evacuated) << ", ";
	ss << "$\\Delta V_{t}=" << Draw::num(volume_total_delta) << "\\%$, ";
	ss << "$\\Delta V_{w}=" << Draw::num(water_volume_delta) << "\\%$, ";
	ss << "$\\Delta V_{nw}=" << Draw::num(oil_volume_delta) << "\\%$, ";

	ss << "time-step=$" << Draw::num(time_step) << "$" << ", ";
	ss << "fluid-added=" << Draw::str(fluid_added) << ", ";
	ss << "fluid-evacuated=" << Draw::str(fluid_evacuated) << ", ";
	ss << "$n_{nodes}=" << n_nodes << "$" << ", ";
	ss << "$n_{tubes}=" << n_tubes << "$" << ", ";
	ss << "$\\sigma=" << Draw::num(sigma) << "$" << ", ";
	ss << "$\\mu_{1}=" << Draw::num(mu_1) << "$" << ", ";
	ss << "$\\mu_{2}=" << Draw::num(mu_2) << "$" << ", ";
	ss << "time step resolution=$" << Draw::num(time_step_resolution) << "$" << ".";

	return ss.str();
}

std::vector<dst::str_pair> visualize::Flow::caption_and_code_multiple_plots(
	dst::States& states,
	const visualize::Property& visual_property
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
