#include "ic/geometry-flow.h"
#include "utility/random.h"

std::tuple<double, double, double, double> ic::GeometryFlow::find_min_max_coordinates(
	const nst::Nodes& nodes
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
	const double n_periods,
	const bool is_skewed
)
{
	auto [nodes, tubes] = GeometryBase::rectangular(
		n_tube_rows,
		n_tube_cols,
		id_fluid_inject
	);

	const auto& [x_min, y_min, x_max, y_max] = find_min_max_coordinates(nodes);
	const double length_system = x_max - x_min;
	const double omega = 2.0 * std::acos(-1) * n_periods / length_system;
	const double x_center = (x_min + x_max) / 2;
	const double y_center = (y_min + y_max) / 2;

	for(auto& tube: tubes)
	{
		const double x1 = nodes[tube.id_node_first].x;
		const double y1 = nodes[tube.id_node_first].y;
		const double x2 = nodes[tube.id_node_second].x;
		const double y2 = nodes[tube.id_node_second].y;
		double x = (x1 + x2) / 2 - x_center;
		const double y = (y1 + y2) / 2 - y_center;
		
		if(is_skewed)
		{
			x = x - 0.5 / n_periods * y;
		}
		
		tube.radius = 1.0 - constant_radius_contrast * std::cos(omega * x) * std::cos(omega * y);
	}

	double sum_radius_square = 0;
	for(const auto& tube: tubes)
	{
		sum_radius_square += std::pow(tube.radius, 2);
	}

	const double temp_radius_term = 1.0 / std::acos(-1) / constant_length_scale / sum_radius_square;
	const double coefficient_radius_scale = std::pow(temp_radius_term, 1.0 / 3);

	for(auto& tube: tubes)
	{
		tube.radius *= coefficient_radius_scale;
		tube.length = coefficient_radius_scale * constant_length_scale;
	}

	return {nodes, tubes};
}


ic::type_pair_nodes_tubes ic::GeometryFlow::network_geometry_const_porosity(
	const int n_tube_rows,
	const int n_tube_cols,
	const int id_fluid_inject,
	const double constant_radius_contrast,
	const double constant_length_scale,
	const double n_periods,
	const bool is_skewed
)
{
	auto [nodes, tubes] = GeometryBase::rectangular(
		n_tube_rows,
		n_tube_cols,
		id_fluid_inject
	);

	const auto& [x_min, y_min, x_max, y_max] = find_min_max_coordinates(nodes);
	const double length_system = x_max - x_min;
	const double omega = 2.0 * std::acos(-1) * n_periods / length_system;
	const double x_center = (x_min + x_max) / 2;
	const double y_center = (y_min + y_max) / 2;
	
	const double k = 1.0 / std::acos(-1) / tubes.size();
	const double A = std::pow(k / constant_length_scale, 1.0 / 3);
	
	for(auto& tube: tubes)
	{
		const double x1 = nodes[tube.id_node_first].x;
		const double y1 = nodes[tube.id_node_first].y;
		const double x2 = nodes[tube.id_node_second].x;
		const double y2 = nodes[tube.id_node_second].y;
		double x = (x1 + x2) / 2 - x_center;
		const double y = (y1 + y2) / 2 - y_center;
		
		if(is_skewed)
		{
			x = x - 0.65 / n_periods * y;
		}
		
		tube.radius = A * (1.0 - constant_radius_contrast * std::cos(omega * x) * std::cos(omega * y));
		tube.length = k / std::pow(tube.radius, 2);
	}

	return {nodes, tubes};
}

ic::type_pair_nodes_tubes ic::GeometryFlow::network_geometry_const_porosity_random_radius(
	const int n_tube_rows,
	const int n_tube_cols,
	const int id_fluid_inject,
	const double constant_radius_contrast,
	const double constant_length_scale
)
{
	static bool need_to_generate_random = true;
	static nst::Nodes nodes_f;
	static nst::Tubes tubes_f;
	
	if(need_to_generate_random)
	{
		auto [nodes, tubes] = GeometryBase::rectangular(
			n_tube_rows,
			n_tube_cols,
			id_fluid_inject
		);


		const double k = 1.0 / std::acos(-1) / tubes.size();
		const double A = std::pow(k / constant_length_scale, 1.0 / 3);
		
		for(auto& tube: tubes)
		{
			const double rational = utility::Random::rational_between_zero_and_one();
			
			tube.radius = A * (1.0 + constant_radius_contrast * 2.0 * (rational - 0.5));
			tube.length = k / std::pow(tube.radius, 2);
		}
		
		need_to_generate_random = false;
		nodes_f = nodes;
		tubes_f = tubes;
	}

	return {nodes_f, tubes_f};
}


ic::type_pair_nodes_tubes ic::GeometryFlow::network_geometry_random_radius(
	const int n_tube_rows,
	const int n_tube_cols,
	const int id_fluid_inject,
	const double constant_radius_contrast,
	const double constant_length_scale
)
{
	static bool need_to_generate_random = true;
	static nst::Nodes nodes_f;
	static nst::Tubes tubes_f;
	
	if(need_to_generate_random)
	{
		auto [nodes, tubes] = GeometryBase::rectangular(
			n_tube_rows,
			n_tube_cols,
			id_fluid_inject
		);


		for(auto& tube: tubes)
		{
			const double rational = utility::Random::rational_between_zero_and_one();
			
			tube.radius = 1.0 + constant_radius_contrast * 2.0 * (rational - 0.5);
		}

		double sum_radius_square = 0;
		for(const auto& tube: tubes)
		{
			sum_radius_square += std::pow(tube.radius, 2);
		}

		const double temp_radius_term = 1.0 / std::acos(-1) / constant_length_scale / sum_radius_square;
		const double coefficient_radius_scale = std::pow(temp_radius_term, 1.0 / 3);

		for(auto& tube: tubes)
		{
			tube.radius *= coefficient_radius_scale;
			tube.length = coefficient_radius_scale * constant_length_scale;
		}
		need_to_generate_random = false;
		nodes_f = nodes;
		tubes_f = tubes;
	}

	return {nodes_f, tubes_f};
}

