#include "ic/geometry-rand.h"


ic::type_pair_nodes_tubes ic::GeometryRand::network_geometry()
{
	auto [nodes, tubes] = ic::GeometryBase::rectangular(2, 4);

	const int n_node_a = nodes.size() - 1;
	nst::Node node;
	node.x = 1.2;
	node.y = 0.4;
	nodes.push_back(node);
	const int n_node_b = nodes.size() - 1;
	nst::Tube tube;
	tube.id_node_first = n_node_a;
	tube.id_node_second = n_node_b;
	tubes.push_back(tube);

	std::vector<std::vector<double>> mpos_possible
	{
		{},
		{0.2},
		{0.3, 0.5},
		{0.1, 0.3, 0.8}
	};

	for(auto& tube: tubes)
	{
		tube.mpos = mpos_possible[utility::Random::integer_from_zero_until_n(mpos_possible.size())];
		tube.fluid_first = utility::Random::integer_from_zero_until_n(2);
	}
	return {nodes, tubes};
}

