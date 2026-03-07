#include "output/visual-dimension.h"

template<class val, class T>
std::pair<val, val> output::VisualDimension::min_max(
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

void output::VisualDimension::node_coordinates(
	dst::State& state,
	const output::Property& visual_property
)
{
	const auto& [min_x, max_x] = min_max(state.nodes, &nst::Node::x);

	const double length = max_x - min_x;

	for(auto& node: state.nodes)
	{
		node.visual.x = node.x / length;
		node.visual.y = node.y / length;
	}
}

void output::VisualDimension::tube_lengths(
	dst::State& state,
	const output::Property& visual_property
)
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

void output::VisualDimension::tube_radius(
	dst::State& state,
	const dst::SystemOutput& system,
	const output::Property& visual_property
)
{
	auto& tubes = state.tubes;
	
	// Use min/max from system parameter instead of calculating
	const double r_min = system.parameter.geometry_distributions.radius.min;
	const double r_max = system.parameter.geometry_distributions.radius.max;

	const double delta_r = r_max - r_min;
	const bool slope_not_possible = ((delta_r / r_max) <= 0.01);
	
	// Find min visual length for scaling
	double length_min = tubes.front().visual.length;
	for(const auto& tube: tubes)
	{
		length_min = std::min(length_min, tube.visual.length);
	}

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

void output::VisualDimension::node_radius(
	dst::State& state,
	const output::Property& visual_property
)
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

double output::VisualDimension::calculate_tube_visual_displacement_due_to_node(
	const double r_node,
	const double r_tube,
	const output::Property& visual_property
)
{
	return std::sqrt(r_node * r_node - r_tube * r_tube);
}

std::vector<double> output::VisualDimension::mpos_long_displaced_scaled(
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

void output::VisualDimension::mpos(
	dst::State& state,
	const output::Property& visual_property
)
{
	const auto& nodes = state.nodes;
	for(auto& tube: state.tubes)
	{
		const auto& node_first = nodes[tube.id_node_first];
		const auto& node_second = nodes[tube.id_node_second];
		const double p1 = calculate_tube_visual_displacement_due_to_node(
			node_first.visual.radius,
			tube.visual.radius,
			visual_property
		);
		const double p2 = calculate_tube_visual_displacement_due_to_node(
			node_second.visual.radius,
			tube.visual.radius,
			visual_property
		);

		tube.visual.mpos = mpos_long_displaced_scaled(tube, p1, p2);
	}
}

void output::VisualDimension::add_state_visual(
	dst::State& state,
	const dst::SystemOutput& system,
	const output::Property& visual_property
)
{
	node_coordinates(state, visual_property);
	tube_lengths(state, visual_property);
	tube_radius(state, system, visual_property);
	node_radius(state, visual_property);
	mpos(state, visual_property);
}
