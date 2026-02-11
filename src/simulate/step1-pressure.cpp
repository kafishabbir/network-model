#include "simulate/step1-pressure.h"

std::pair<dst::Matrix, std::vector<double>>
simulate::Step1Pressure::generate_linear_equations(
	const nst::State& state
)
{
	const int n_nodes = state.nodes.size();
	dst::Matrix A(n_nodes, std::vector<double>(n_nodes));
	std::vector<double> B(n_nodes);

	for(int i = 0; i < n_nodes; ++ i)
	{
		const auto& node = state.nodes[i];
		auto& row = A[i];
		auto& b = B[i];

		if(node.is_open_boundary)
		{
			row[i] = 1;
			b = node.pressure;
			continue;
		}

		const auto& tubes_connected_to_node = node.calculated.connections_id_tube_v;
		const int n_connections = tubes_connected_to_node.size();
		for(int j = 0; j < n_connections; ++ j)
		{
			const int id_tube = tubes_connected_to_node[j];
			const auto& tube = state.tubes[id_tube];
			const int id_node_second = tube.id_other_node(i);

			const double resistance = tube.calculated.resistance_coefficient;
			const double capillary_pressure_magnitude = tube.calculated.capillary_pressure_magnitude;
			const double capillary_pressure_sign = simulate::Physics::determine_capillary_pressure_sign(tube, i);
			const double capillary_pressure = capillary_pressure_magnitude * capillary_pressure_sign;

			row[i] += resistance;
			row[id_node_second] = -resistance;

			b -= resistance * capillary_pressure;
		}
	}

	return {A, B};
}

void simulate::Step1Pressure::assign_pressures_to_each_node(
	dst::Nodes& nodes,
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
	nst::State& state
)
{
	simulate::StepPreparation::assign_resistance_to_tubes(state);
	simulate::StepPreparation::assign_capillary_pressure_magnitude_to_tubes(state);

	const auto& [A, B] = generate_linear_equations(state);
	const auto& known_pressures = utility::Math::gaussian_elimination(A, B);
	assign_pressures_to_each_node(state.nodes, known_pressures);
}
