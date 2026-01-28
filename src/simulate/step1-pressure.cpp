#include "simulate/step1-pressure.h"

Matrix simulate::Step1Pressure::generate_linear_equations(
	const State& state
)
{
	const int n_nodes = state.nodes.size();
	Matrix gauss_matrix(n_nodes, std::vector<double>(n_nodes + 1));

	for(int i = 0; i < n_nodes; ++ i)
	{
		const auto& node = state.nodes[i];
		auto& gauss_row = gauss_matrix[i];
		if(node.is_open_boundary)
		{
			gauss_row[i] = 1;
			gauss_row.back() = node.pressure;
			continue;
		}

		const auto& tubes_connected_to_node = state.tubes_connected_to_this_node(i);
		const int n_connections = tubes_connected_to_node.size();
		for(int j = 0; j < n_connections; ++ j)
		{
			const int tube_id = tubes_connected_to_node[j];
			const auto& tube = state.tubes[tube_id];
			const int id_node_second = tube.id_other_node(i);
			const double a = simulate::Physics::calculate_a(tube, state);
			gauss_row[i] += a;
			gauss_row[id_node_second] -= a;
		}
	}

	return gauss_matrix;
}

void simulate::Step1Pressure::assign_pressures_to_each_node(
	Nodes& nodes,
	const std::vector<double>& pressures
)
{
	const int n_nodes = nodes.size();
	for(int i = 0; i < n_nodes; ++ i)
	{
		auto& node = nodes[i];
		node.pressure = pressures[i];
	}
}

void simulate::Step1Pressure::solve_and_assign_pressure_at_nodes(
	State& state
)
{
	auto linear_equaitions = generate_linear_equations(state);
	const std::vector<double>& known_pressures = utility::Math::gaussian_elimination(linear_equaitions);
	assign_pressures_to_each_node(state.nodes, known_pressures);
}
