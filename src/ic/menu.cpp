#include "ic/menu.h"

ic::type_pair_nodes_tubes ic::Menu::network_geometry_base(
	const int n_tube_rows,
	const int n_tube_cols
)
{
	return ic::GeometryBase::rectangular(n_tube_rows, n_tube_cols);
}

ic::type_pair_nodes_tubes ic::Menu::network_geometry_flow()
{
	return ic::GeometryFlow::network_geometry();
}

ic::type_pair_nodes_tubes ic::Menu::network_geometry_rand()
{
	return ic::GeometryRand::network_geometry();
}
