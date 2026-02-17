#include "ic/geometry-flow.h"


std::tuple<double, double, double, double> ic::GeometryFlow::find_min_max_coordinates(
	const dst::Nodes& nodes
)
{
	double x_min = nodes.front().x;
	double y_min = nodes.front().y;

	double x_max = nodes.front().x;
	double y_max = nodes.front().y;

	for(const auto& node: nodes)
	{
		x_min = std::min(node.x, x_min);
		y_min = std::min(node.y, y_min);

		x_max = std::max(node.x, x_max);
		y_max = std::max(node.y, y_max);
	}

	return {x_min, y_min, x_max, y_max};
}

ic::type_pair_nodes_tubes ic::GeometryFlow::network_geometry(
	const int n_tube_rows,
	const int n_tube_cols,
	const int id_fluid_inject,
	const double constant_radius_contrast,
	const double constant_length_scale,
	const double n_periods
)
{
	auto [nodes, tubes] = GeometryBase::rectangular(
		n_tube_rows,
		n_tube_cols,
		id_fluid_inject
	);

	const auto& [x_min, y_min, x_max, y_max] = find_min_max_coordinates(nodes);
	const double length_system = x_max - x_min;
	const double omega = 2.0 * decl::pi * n_periods / length_system;
	const double x_center = (x_min + x_max) / 2;
	const double y_center = (y_min + y_max) / 2;

	for(auto& tube: tubes)
	{
		const double x1 = nodes[tube.id_node_first].x;
		const double y1 = nodes[tube.id_node_first].y;
		const double x2 = nodes[tube.id_node_second].x;
		const double y2 = nodes[tube.id_node_second].y;
		const double x = (x1 + x2) / 2 - x_center;
		const double y = (y1 + y2) / 2 - y_center;

		tube.radius = 1.0 - constant_radius_contrast * std::cos(omega * x) * std::cos(omega * y);
	}

	double sum_radius_square = 0;
	for(const auto& tube: tubes)
	{
		sum_radius_square += std::pow(tube.radius, 2);
	}

	const double temp_radius_term = 1.0 / decl::pi / constant_length_scale / sum_radius_square;
	const double coefficient_radius_scale = std::pow(temp_radius_term, 1.0 / 3);

	for(auto& tube: tubes)
	{
		tube.radius *= coefficient_radius_scale;
		tube.length = coefficient_radius_scale * constant_length_scale;
	}

	return {nodes, tubes};
}


