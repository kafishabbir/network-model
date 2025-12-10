#include "generator/ic.h"

int calculate_total_nodes(int nrows, int ncols)
{
	int cols_on_even_rows = ncols / 2 + 1;
	int cols_on_odd_rows = (ncols + 1) / 2;

	int even_rows = nrows / 2 + 1;
	int odd_rows = (nrows + 1) / 2;

	return even_rows * cols_on_even_rows + odd_rows * cols_on_odd_rows;
}

std::pair<std::vector<nst::Node>, std::vector<nst::Tube>>
	generator::Ic::square_lattice(int nrows, int ncols)
{
	const int n_nodes = calculate_total_nodes(nrows, ncols);
	std::vecotor<nst::Node> v_nodes(n_nodes);

	const int nodes_on_even_rows = ncols / 2 + 1;
	const int nodes_on_odd_rows = (ncols + 1) / 2;

	const int n_rows_of_nodes = nrows + 1;

	const double max_n_tubes_in_xy = std::max<double>(nrows, ncols);
	const double displacement_step = 1.0 / max_n_tubes_in_xy;

	double y = ncols * displacement_step;
	for(int i = 0, node_i = 0; i < n_rows_of_nodes; ++ i)
	{
		const bool even_row = (nrows % 2) == 0);
		const int n_cols = (even_row ? nodes_on_even_rows : nodes_on_odd_rows);
		double x = (even_row ? 0 : displacement_step);
		for(int j = 0; j < n_cols; ++ j)
		{
			auto& node = v_nodes[node_i++];
			node.x = x;
			node.y = y;
			x += 2.0 * displacement_step;
		}
		y -= displacement_step;
	}






}
