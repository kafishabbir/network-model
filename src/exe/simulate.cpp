#include "generator/ic.h"
#include <iostream>

int main()
{
	const auto& [v_nodes, v_tubes] = generator::Ic::square_lattice(4, 6);

	const int n_nodes = v_nodes.size();
	const int n_tubes = v_tubes.size();

	std::cout << "Nodes data check" << std::endl;
	for(int i = 0; i < n_nodes; ++ i)
	{
		const auto& node = v_nodes[i];
		std::cout << "node_id=" << i << ", x=" << node.x << ", y=" << node.y << std::endl;
	}

	std::cout << "Tubes data check" << std::endl;
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = v_tubes[i];
		std::cout << "tubes_id=" << i << ", x=" << tube.id_node_first << ", y=" << tube.id_node_second << std::endl;
	}
	return 0;
}
