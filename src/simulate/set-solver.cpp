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
		if(node.is_open_boundary && node.is_pressure_known)
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
	
	const int n_nodes = system.state.nodes.size();
	for(int id_node_a = 0; id_node_a < n_nodes; ++ id_node_a)
	{
		const auto& node_a = system.state.nodes[id_node_a];
		if(node_a.is_pressure_known)
		{
			continue;
		}
		
		const int id_symmetric_a = node_a.reference.id_for_symmetric_matrix;
		triplets.push_back(Eigen::Triplet<double>(id_symmetric_a, id_symmetric_a, 1.0));
		
		for(const int id_tube: node_a.reference.connections_id_tube_v)
		{
			const auto& tube = system.state.tubes[id_tube];
			const int id_node_b = (tube.id_node_first == id_node_a) ? tube.id_node_second : tube.id_node_first;
			const auto& node_b = system.state.nodes[id_node_b];
			
			if(node_b.is_pressure_known)
			{
				continue;
			}
			
			const int id_symmetric_b = node_b.reference.id_for_symmetric_matrix;
			triplets.push_back(Eigen::Triplet<double>(id_symmetric_a, id_symmetric_b, 1.0));
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
