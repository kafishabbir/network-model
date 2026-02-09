#include "visualize/re-scale-state-for-plot.h"

template<class val, class T>
std::pair<val, val> visualize::ReScaleStateForPlot::min_max(
	const std::vector<T>& v,
	val T::*member
)
{
    val min_val = v.front().*member;
    val max_val = v.front().*member;
    for(const auto& x : v)
    {
        min_val = std::min(min_val, x.*member);
        max_val = std::max(max_val, x.*member);
    }

    return {min_val, max_val};
}

template<class val, class T, class U>
std::pair<val, val> visualize::ReScaleStateForPlot::min_max(
    const std::vector<T>& v,
    U T::*member,  // Pointer to member U in T
    val U::*submember  // Pointer to member val in U
)
{
    val min_val = (v.front().*member).*submember;
    val max_val = (v.front().*member).*submember;
    for(const auto& x : v)
    {
        min_val = std::min(min_val, (x.*member).*submember);
        max_val = std::max(max_val, (x.*member).*submember);
    }

    return {min_val, max_val};
}

void visualize::ReScaleStateForPlot::node_coordinates(nst::State& state)
{
	const auto& [min_x, max_x] = min_max(state.nodes, &nst::Node::x);

	const double length = max_x - min_x;

	for(auto& node: state.nodes)
	{
		node.visual.x = node.x / length;
		node.visual.y = node.y / length;
	}
}


void visualize::ReScaleStateForPlot::tube_lengths(nst::State& state)
{
	auto& tubes = state.tubes;
	auto& nodes = state.nodes;

	for(auto& tube: tubes)
	{
		const auto& node_first = nodes[tube.id_node_first];
		const auto& node_second = nodes[tube.id_node_second];
		tube.visual.length = node_first.visual.distance(node_second);
	}
}

void visualize::ReScaleStateForPlot::tube_radius(nst::State& state)
{
	auto& tubes = state.tubes;
	const auto& [r_min, r_max] = min_max(tubes, &nst::Tube::radius);

	const double delta_r = r_max - r_min;
	const bool slope_not_possible = ((delta_r / r_max) <= 0.01);
	const auto& [length_min, length_max] = min_max(tubes, &nst::Tube::visual, &nst::Tube::Visual::length);

	if(slope_not_possible)
	{
		for(auto& tube: tubes)
		{
			tube.visual.radius = length_min * (decl::nps_latex_plot::nps_flow::nps_parameters::tube_radius_min + decl::nps_latex_plot::nps_flow::nps_parameters::tube_radius_max) / 2;
		}
		return;
	}
	const double DELTA_R = decl::nps_latex_plot::nps_flow::nps_parameters::tube_radius_max - decl::nps_latex_plot::nps_flow::nps_parameters::tube_radius_min;

	for(auto& tube: tubes)
	{
		tube.visual.radius = length_min * (
			decl::nps_latex_plot::nps_flow::nps_parameters::tube_radius_min + DELTA_R / delta_r * (tube.radius - r_min)
		);
	}
}

void visualize::ReScaleStateForPlot::node_radius(nst::State& state)
{
	auto& nodes = state.nodes;
	const int n_nodes = nodes.size();

	for(int i = 0; i < n_nodes; ++ i)
	{
		auto& node = nodes[i];
		const auto& tube_id_v = state.table_tubes_connected_to_nodes[i];

		double radius_max = 0;
		//std::cout << "node_id=" << i << '\n';
		for(const int tube_id: tube_id_v)
		{
			radius_max = std::max(state.tubes[tube_id].visual.radius, radius_max);
			//std::cout << "tube_id=" << tube_id << ", visual.radius=" << state.tubes[tube_id].visual.radius << ", max_radius=" << radius_max << '\n';
		}
		//std::cout << '\n';

		const auto theta = decl::nps_latex_plot::nps_flow::nps_parameters::largest_angle_tube_project_on_node;
		node.visual.radius = radius_max / std::sin(theta / 2.0);
	}
}

double visualize::ReScaleStateForPlot::calculate_tube_visual_displacement_due_to_node(
	const double r_node,
	const double r_tube
)
{
	if(decl::nps_latex_plot::nps_flow::nps_feature::draw_node_perimeter)
	{
		return std::sqrt(r_node * r_node - r_tube * r_tube);
	}

	return 0;
}


void visualize::ReScaleStateForPlot::mpos(nst::State& state)
{
	//int i = 0;
	const auto& nodes = state.nodes;
	for(auto& tube: state.tubes)
	{
		const auto& node_first = nodes[tube.id_node_first];
		const auto& node_second = nodes[tube.id_node_second];
		const double p1 = calculate_tube_visual_displacement_due_to_node(node_first.visual.radius, tube.visual.radius);
		const double p2 = calculate_tube_visual_displacement_due_to_node(node_second.visual.radius, tube.visual.radius);

		//std::cout << "tube_id=" << i++ << '\n';
		//std::cout << "node_first.visual.radius=" << node_first.visual.radius << '\n';
		//std::cout << "node_second.visual.radius=" << node_second.visual.radius << '\n';
		//std::cout << "tube.visual.radius=" << tube.visual.radius << '\n';
		//std::cout << "p1=" << p1 << ", p2=" << p2 << '\n';

		tube.visual.mpos = tube.mpos_long_displaced_scaled(p1, p2);
	}

}

void visualize::ReScaleStateForPlot::add_state_visual(
	nst::State& state
)
{
	node_coordinates(state);
	tube_lengths(state);
	tube_radius(state);
	node_radius(state);
	mpos(state);
}
