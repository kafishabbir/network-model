#include "visualize/re-scale-state-for-plot.h"

template<class val, class T>
std::pair<val, val> visualize::ReScaleStateForPlot::min_max(
	const std::vector<T>& v,
	val T::*member
)
{
    val val_min = v.front().*member;
    val val_max = v.front().*member;
    for(const auto& x : v)
    {
        val_min = std::min(val_min, x.*member);
        val_max = std::max(val_max, x.*member);
    }

    return {val_min, val_max};
}

template<class val, class T, class U>
std::pair<val, val> visualize::ReScaleStateForPlot::min_max(
    const std::vector<T>& v,
    U T::*member,  // Pointer to member U in T
    val U::*submember  // Pointer to member val in U
)
{
    val val_min = (v.front().*member).*submember;
    val val_max = (v.front().*member).*submember;
    for(const auto& x : v)
    {
        val_min = std::min(val_min, (x.*member).*submember);
        val_max = std::max(val_max, (x.*member).*submember);
    }

    return {val_min, val_max};
}

void visualize::ReScaleStateForPlot::node_coordinates(nst::State& state, const visualize::Property& visual_property)
{
	const auto& [min_x, max_x] = min_max(state.nodes, &nst::Node::x);

	const double length = max_x - min_x;

	for(auto& node: state.nodes)
	{
		node.visual.x = node.x / length;
		node.visual.y = node.y / length;
	}
}


void visualize::ReScaleStateForPlot::tube_lengths(nst::State& state, const visualize::Property& visual_property)
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

void visualize::ReScaleStateForPlot::tube_radius(nst::State& state, const visualize::Property& visual_property)
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
			tube.visual.radius = length_min * (visual_property.tube_radius_min + visual_property.tube_radius_max) / 2;
		}
		return;
	}
	const double DELTA_R = visual_property.tube_radius_max - visual_property.tube_radius_min;

	for(auto& tube: tubes)
	{
		tube.visual.radius = length_min * (
			visual_property.tube_radius_min + DELTA_R / delta_r * (tube.radius - r_min)
		);
	}
}

void visualize::ReScaleStateForPlot::node_radius(nst::State& state, const visualize::Property& visual_property)
{
	auto& nodes = state.nodes;
	const int n_nodes = nodes.size();

	for(int i = 0; i < n_nodes; ++ i)
	{
		auto& node = nodes[i];
		const auto& id_tube_v = node.reference.connections_id_tube_v;

		double radius_max = 0;
		for(const int id_tube: id_tube_v)
		{
			radius_max = std::max(state.tubes[id_tube].visual.radius, radius_max);
		}

		const auto theta = visual_property.largest_angle_tube_project_on_node;
		node.visual.radius = radius_max / std::sin(theta / 2.0);
	}
}

double visualize::ReScaleStateForPlot::calculate_tube_visual_displacement_due_to_node(
	const double r_node,
	const double r_tube, const visualize::Property& visual_property
)
{
	if(visual_property.draw_node_perimeter)
	{
		return std::sqrt(r_node * r_node - r_tube * r_tube);
	}

	return 0;
}

std::vector<double> visualize::ReScaleStateForPlot::mpos_long_displaced_scaled(
	const nst::Tube& tube,
	const double p1,
	const double p2
)
{
	auto v = tube.mpos_long();
	const double length_effective = tube.visual.length - p1 - p2;
	for(auto& x: v)
	{
		x = p1 + length_effective * x;
	}
	return v;

}

void visualize::ReScaleStateForPlot::mpos(nst::State& state, const visualize::Property& visual_property)
{
	//int i = 0;
	const auto& nodes = state.nodes;
	for(auto& tube: state.tubes)
	{
		const auto& node_first = nodes[tube.id_node_first];
		const auto& node_second = nodes[tube.id_node_second];
		const double p1 = calculate_tube_visual_displacement_due_to_node(node_first.visual.radius, tube.visual.radius, visual_property);
		const double p2 = calculate_tube_visual_displacement_due_to_node(node_second.visual.radius, tube.visual.radius, visual_property);

		tube.visual.mpos = mpos_long_displaced_scaled(tube, p1, p2);
	}

}

void visualize::ReScaleStateForPlot::add_state_visual(
	nst::State& state, const visualize::Property& visual_property
)
{
	node_coordinates(state, visual_property);
	tube_lengths(state, visual_property);
	tube_radius(state, visual_property);
	node_radius(state, visual_property);
	mpos(state, visual_property);
}
