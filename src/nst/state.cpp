#include "nst/state.h"

nst::State::State(
	const std::vector<nst::Node>& nodes,
	const std::vector<nst::Tube>& tubes,
	const double mu1,
	const double mu2,
	const double sigma,
	const double time_step_resolution
):
	nodes(nodes),
	tubes(tubes),
	mu1(mu1),
	mu2(mu2),
	sigma(sigma),
	time_step_resolution(time_step_resolution),
	table_tubes_connected_to_nodes(generate_table_tubes_connected_to_nodes())
{}

std::vector<std::vector<int>> nst::State::generate_table_tubes_connected_to_nodes() const
{
	const int n_nodes = nodes.size();
	std::vector<std::vector<int>> v(n_nodes);

	const int n_tubes = tubes.size();
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = tubes[i];
		const int id_node_first = tube.id_node_first;
		const int id_node_second = tube.id_node_second;

		v[id_node_first].push_back(i);
		v[id_node_second].push_back(i);
	}

	return v;
}

std::vector<int> nst::State::tubes_connected_to_this_node(const int id_node) const
{
	return table_tubes_connected_to_nodes[id_node];
}
