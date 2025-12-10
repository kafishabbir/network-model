#include "generator/ic.h"

int calculate_total_nodes(int nrows, int ncols)
{
	int cols_on_even_rows = ncols/2 + 1;
	int cols_on_odd_rows = (ncols + 1) / 2;

	int even_rows = nrows / 2 + 1;
	int odd_rows = (nrows + 1) / 2;

	return even_rows * cols_on_even_rows + odd_rows * cols_on_odd_rows;
}

std::pair<std::vector<nst::Node>, std::vector<nst::Tube>>
	generator::Ic::square_lattice(int nrows, int ncols)
{
	const int n_nodes = calculate_total_nodes(nrows, ncols);
	std::vecotor<>

}
