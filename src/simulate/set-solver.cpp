#include "simulate/set-solver.h"

void simulate::SetSolver::assign_symmetric_id_to_nodes(
	dst::System& system
)
{
	int count = 0;
	const int n_nodes = system.state.nodes.size();
	
	for(int id_node = 0; id_node < n_nodes; ++ id_node)
	{
		auto& node = system.state.nodes[id_node];
		if(node.is_pressure_known)
		{
			continue;
		}
		
		node.reference.id_for_symmetric_matrix = count;
		system.id_nodes_unknown_pressure_v.push_back(id_node);
		++ count;
	}
}

void simulate::SetSolver::fill_sparse_matrix(
	dst::System& system
)
{
	std::vector<Eigen::Triplet<double>> triplets;
	const int n_tubes = system.state.tubes.size();
	
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = system.state.tubes[i];
		const auto& node_a = system.state.nodes[tube.id_node_first];
		const auto& node_b = system.state.nodes[tube.id_node_second];
		
		std::vector<std::pair<int, bool>> v
		{
			{node_a.reference.id_for_symmetric_matrix, !node_a.is_pressure_known},
			{node_b.reference.id_for_symmetric_matrix, !node_b.is_pressure_known}
		};
		
		for(const auto& a: v)
		{
			for(const auto& b: v)
			{
				if(a.first >= 0 && b.first >= 0)
				{
					triplets.push_back(Eigen::Triplet<double>(a.first, b.first, 1.0));
				}
			}
		}
	}
	
	const int n_unknown = system.id_nodes_unknown_pressure_v.size();
	system.sparse_matrix.resize(n_unknown, n_unknown);
	system.sparse_matrix.setFromTriplets(triplets.begin(), triplets.end());
}

void simulate::SetSolver::analyze_pattern(
	dst::System& system
)
{
	system.solver.analyzePattern(system.sparse_matrix);
}

void simulate::SetSolver::run(
	dst::System& system
)
{
	assign_symmetric_id_to_nodes(system);
	fill_sparse_matrix(system);
	analyze_pattern(system);
}
