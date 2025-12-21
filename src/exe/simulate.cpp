#include "generator/ic.h"
#include "plot/flow.h"
#include <iostream>

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

int main()
{
	std::vector<std::pair<Nodes, Tubes>> v;
	for(int j = 0; j < 10; ++ j)
	{
		auto [v_nodes, v_tubes] = generator::Ic::square_lattice(4, 6);
		const int n_tubes = v_tubes.size();
		for(int i = 0; i < n_tubes; ++ i)
		{
			auto& tube = v_tubes[i];
			const int mpos_combinations_size = mpos_combinations.size();
			tube.mpos = mpos_combinations[(j * i + j + i) % mpos_combinations_size];
			const int radius_possible_size = radius_possible.size();
			tube.fluid_first = (i * j + j + i) % 2;
			tube.radius = radius_possible[(3 * i * j + i + j) % radius_possible_size];
		}

		nst::Tube add_tube;
		add_tube.id_node_first = 10;
		add_tube.id_node_second = 18;
		add_tube.mpos = std::vector<double>{0.1, 0.3, 0.5, 0.7};
		v_tubes.push_back(add_tube);

		nst::Node add_node;
		add_node.x = 1.1;
		add_node.y = -0;
		v_nodes.push_back(add_node);


		v.push_back({v_nodes, v_tubes});
	}

	plot::Flow::mpos_multiple_plots_in_1_pdf(v);

	return 0;
}
