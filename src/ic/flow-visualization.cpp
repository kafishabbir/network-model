#include "ic/flow-visualization.h"


nst::Nodes ic::FlowVisualization::generate_nodes_rectangular(
	const int n_rows_tube,
	const int n_cols_tube
)
{
	const int n_cols_node_at_even_rows = n_cols_tube / 2 + 1;
	const int n_cols_node_at_odd_rows  = (n_cols_tube + 1) / 2;

	const int n_even_rows_node = n_rows_tube / 2 + 1;
	const int n_odd_rows_node = (n_rows_tube + 1) / 2;

	const int n_nodes =
		n_cols_node_at_even_rows * n_even_rows_node +
		n_cols_node_at_odd_rows * n_odd_rows_node;

	nst::Nodes nodes(n_nodes);
	const int n_rows_node = n_rows_tube + 1;

	// const double n_tubes_max_in_xy = std::max<double>(n_rows_tube, n_cols_tube);
	// const double displacement_step = 1.0 / n_tubes_max_in_xy;
	const double n_cols_tube_double = n_cols_tube;
	const double displacement_step = 1.0 / n_cols_tube_double;
	// makes the longest side length of the system equal to 1.0

	double y = n_rows_tube * displacement_step;
	for(int i = 0, node_id = 0; i < n_rows_node; ++ i)
	{
		const bool is_it_even_row = ((i % 2) == 0);
		const int n_cols_node =
			(is_it_even_row ? n_cols_node_at_even_rows : n_cols_node_at_odd_rows);
		double x = (is_it_even_row ? 0 : displacement_step);
		for(int j = 0; j < n_cols_node ; ++ j)
		{
			auto& node = nodes[node_id];
			++ node_id;
			node.x = x;
			node.y = y;
			x += 2.0 * displacement_step;
		}
		y -= displacement_step;
	}

	return nodes;
}

nst::Tubes ic::FlowVisualization::generate_tubes_rectangular(
	const int n_rows_tube,
	const int n_cols_tube
)
{
	const int n_cols_node_at_even_rows = n_cols_tube / 2 + 1;
	int node_up = 0;
	int node_down = n_cols_node_at_even_rows;
	const int n_tubes = n_rows_tube * n_cols_tube;
	nst::Tubes tubes(n_tubes);
	for(int i = 0; i < n_rows_tube; ++ i)
	{
		int up_adder = (i + 1) % 2;
		int down_adder = i % 2;
		for(int j = 0; j < n_cols_tube; ++ j)
		{
			auto& tube = tubes[i * n_cols_tube + j];
			tube.id_node_first = node_up;
			tube.id_node_second = node_down;

			node_up += up_adder;
			node_down += down_adder;

			up_adder = (up_adder + 1) % 2;
			down_adder = (down_adder + 1) % 2;
		}
		node_up += up_adder;
		node_down += down_adder;
	}

	return tubes;
}

nst::State ic::FlowVisualization::generate_rectangular(
	const int n_rows_tube,
	const int n_cols_tube
)
{
	const auto& nodes =
		generate_nodes_rectangular(n_rows_tube, n_cols_tube);
	const auto& tubes =
		generate_tubes_rectangular(n_rows_tube, n_cols_tube);

	return nst::State(nodes, tubes);
}

nst::nst::States ic::FlowVisualization::generate_states_rectangular_plus_random()
{
	const std::vector<std::vector<double>> mpos_combinations
	{
		{0.3},
		{0.1, 0.7},
		{},
		{0.6},
		{},
		{0.2, 0.4},
		{0.4}
	};

	const std::vector<double> radius_possible
	{
		1,
		4,
		3,
		8,
		2
	};

	nst::nst::States v;
	for(int j = 0; j < 10; ++ j)
	{
		nst::State state = generate_rectangular(4, 6);
		auto& tubes = state.tubes;
		auto& nodes = state.nodes;
		const int n_tubes = tubes.size();
		for(int i = 0; i < n_tubes; ++ i)
		{
			auto& tube = tubes[i];
			const int mpos_combinations_size = mpos_combinations.size();
			const int rand_int_mpos = utility::Random::integer_from_zero_until_n(mpos_combinations_size);
			tube.mpos = mpos_combinations[rand_int_mpos];
			const int radius_possible_size = radius_possible.size();
			const int rand_int_radius = utility::Random::integer_from_zero_until_n(radius_possible_size);
			tube.fluid_first =  utility::Random::integer_from_zero_until_n(2);
			tube.radius = radius_possible[rand_int_radius];
		}

		nst::Tube add_tube;
		add_tube.id_node_first = 10;
		add_tube.id_node_second = 18;
		add_tube.mpos = std::vector<double>{0.1, 0.3, 0.5, 0.7};
		tubes.push_back(add_tube);

		nst::Node add_node;
		add_node.x = 1.1;
		add_node.y = -0;
		nodes.push_back(add_node);

		v.push_back(state);
	}

	return v;
}
