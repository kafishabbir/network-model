#include "ic/geometry-multiple-tubes-between-nodes.h"
#include "utility/random.h"

ic::type_pair_nodes_tubes ic::GeometryMultipleTubesBetweenNodes::network_geometry_real(
	const int n_tube_rows,
	const int n_tube_cols,
	const int id_fluid_inject,
	const double constant_length_scale
)
{
	const double radius_thickest_tube = 1e-4;
	const int n_tubes_between_a_pair_of_nodes = 3;
	const double ratio_between_radii_tubes = 5;
	const double length_tubes = constant_length_scale * radius_thickest_tube;
	
	static bool is_generation_needed_with_rand = true;
	
	static nst::Nodes nodes_f;
	static nst::Tubes tubes_f;
	
	
	
	//~ for(const auto& tube: tubes)
	//~ {
		//~ std::cout << "tube: node-a=" << tube.id_node_first << ", node-b=" << tube.id_node_second << std::endl;
	//~ }
	
	//~ for(const auto& node: nodes)
	//~ {
		//~ std::cout << "x=" << node.x << ", y=" << node.y << std::endl;
	//~ }
	if(is_generation_needed_with_rand)
	{
		auto [nodes, tubes] = GeometryBase::rectangular(
			n_tube_rows,
			n_tube_cols,
			id_fluid_inject
		);
	
		nst::Tubes tubes_addition;
		for(auto& tube: tubes)
		{
			tube.radius = radius_thickest_tube;
			tube.length = length_tubes;
			double current_radius = tube.radius;
			for(int i = 1; i < n_tubes_between_a_pair_of_nodes; ++ i)
			{
				auto tube_addition(tube);
				current_radius /= ratio_between_radii_tubes;
				tube_addition.radius = current_radius + utility::Random::small_noise();
				tube_addition.length += current_radius + utility::Random::small_noise();
				tubes_addition.push_back(tube_addition);
			}
		}
		
		tubes.insert(tubes.end(), tubes_addition.begin(), tubes_addition.end());
		
		is_generation_needed_with_rand = false;
		
		nodes_f = nodes;
		tubes_f = tubes;
	}
	
	return {nodes_f, tubes_f};
}

