#include "ic/geometry-base.h"

dst::Nodes ic::GeometryBase::rectangular_nodes(
	const int n_tube_rows,
	const int n_tube_cols
)
{
	const int n_cols_node_at_even_rows = n_tube_cols / 2 + 1;
	const int n_cols_node_at_odd_rows  = (n_tube_cols + 1) / 2;

	const int n_even_rows_node = n_tube_rows / 2 + 1;
	const int n_odd_rows_node = (n_tube_rows + 1) / 2;

	const int n_nodes =
		n_cols_node_at_even_rows * n_even_rows_node +
		n_cols_node_at_odd_rows * n_odd_rows_node;

	dst::Nodes nodes(n_nodes);
	const int n_rows_node = n_tube_rows + 1;

	// const double n_tubes_max_in_xy = std::max<double>(n_tube_rows, n_tube_cols);
	// const double displacement_step = 1.0 / n_tubes_max_in_xy;
	const double n_tube_cols_double = n_tube_cols;
	const double displacement_step = 1.0 / n_tube_cols_double;
	// makes the longest side length of the system equal to 1.0

	double y = n_tube_rows * displacement_step;
	for(int i = 0, id_node = 0; i < n_rows_node; ++ i)
	{
		const bool is_it_even_row = ((i % 2) == 0);
		const int n_cols_node =
			(is_it_even_row ? n_cols_node_at_even_rows : n_cols_node_at_odd_rows);
		double x = (is_it_even_row ? 0 : displacement_step);
		for(int j = 0; j < n_cols_node ; ++ j)
		{
			auto& node = nodes[id_node];
			++ id_node;
			node.x = x;
			node.y = y;
			x += 2.0 * displacement_step;
		}
		y -= displacement_step;
	}

	return nodes;
}



std::vector<nst::Tube> ic::GeometryBase::rectangular_tubes(
	const int n_tube_rows,
	const int n_tube_cols
)
{
	const int n_cols_node_at_even_rows = n_tube_cols / 2 + 1;
	int node_up = 0;
	int node_down = n_cols_node_at_even_rows;
	const int n_tubes = n_tube_rows * n_tube_cols;
	std::vector<nst::Tube> tubes(n_tubes);
	for(int i = 0; i < n_tube_rows; ++ i)
	{
		int up_adder = (i + 1) % 2;
		int down_adder = i % 2;
		for(int j = 0; j < n_tube_cols; ++ j)
		{
			auto& tube = tubes[i * n_tube_cols + j];
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

ic::type_pair_nodes_tubes ic::GeometryBase::rectangular(
	const int n_tube_rows,
	const int n_tube_cols
)
{
	const auto& nodes =
		rectangular_nodes(n_tube_rows, n_tube_cols);
	const auto& tubes =
		rectangular_tubes(n_tube_rows, n_tube_cols);

	return {nodes, tubes};
}

