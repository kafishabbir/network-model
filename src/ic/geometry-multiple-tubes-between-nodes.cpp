#include "ic/geometry-multiple-tubes-between-nodes.h"

ic::GeometryMultipleTubesBetweenNodes::network_geometry_real(
	const int n_tube_rows,
	const int n_tube_cols,
	const int id_fluid_inject,
	const double constant_length_scale
)
{
	const double radius_thickest_tube = 0.0001;
	const int n_tubes_between_a_pair_of_nodes = 3;
	const double ratio_between_radii_tubes = 2;
	const double length_tubes = constant_length_scale * radius_thickest_tube;
	
	auto [nodes, tubes] = GeometryBase::rectangular(
		n_tube_rows,
		n_tube_cols,
		id_fluid_inject
	);
	
	dst::Tubes tubes_addition;
	for(auto& tube: tubes)
	{
		tube.radius = radius_thickest_tube;
		tube.length = length_tubes;
		double current_radius = tube.radius;
		for(int i = 0; i < n_tubes_between_a_pair_of_nodes; ++ i)
		{
			auto tube_addition(tube);
			current_radius /= ratio_between_radii_tubes;
			tube_addition.radius = current_radius;
			tubes_addition.push_back(tube_addition);
		}
	}
	
	tubes.insert(tubes.begin(), tubes_addition.begin(), tubes_addition.end());
	
	return {nodes, tubes};
}

