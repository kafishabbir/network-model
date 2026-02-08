#include "ic/displacement-test.h"

nst::Nodes ic::DisplacementTest::generate_nodes_rectangular(
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

nst::Tubes ic::DisplacementTest::generate_tubes_rectangular(
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

nst::State ic::DisplacementTest::generate_rectangular(
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

nst::State ic::DisplacementTest::generate_rectangular()
{
	return generate_rectangular(2, 4);
}
