#include "simulate/step2-pressure.h"


std::pair<dst::Matrix, std::vector<double>> simulate::Step2Pressure::generate_linear_equations(
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
			row[i] = 1.0;
			b = node.pressure;
			continue;
		}

		const auto& connections_id_tube_v = node.calculated.connections_id_tube_v;
		const int n_connections = connections_id_tube_v.size();
		for(int j = 0; j < n_connections; ++ j)
		{
			const int id_tube = connections_id_tube_v[j];
			const auto& tube = state.tubes[id_tube];

			const double sign = ((tube.id_node_first == i) ? 1 : -1);

			const int id_node_b = ((sign < 0) ? tube.id_node_first: tube.id_node_second);

			const double resistance = tube.calculated.resistance_coefficient;
			const double capillary_pressure =
				sign * tube.calculated.capillary_pressure_magnitude;

			row[i] += resistance;
			row[id_node_b] = -resistance;

			b -= resistance * capillary_pressure;
		}
	}

	return {A, B};
}


std::vector<double> simulate::Step2Pressure::choose_method_of_solving_linear_equations(
	const dst::Matrix& A,
	const std::vector<double>& B
)
{
	return utility::Math::gaussian_elimination(A, B);
}


void simulate::Step2Pressure::assign_pressure_v_to_each_node(
	nst::State& state,
	const std::vector<double>& pressure_v
)
{
	const int n_nodes = state.nodes.size();
	for(int i = 0; i < n_nodes; ++ i)
	{
		state.nodes[i].calculated.pressure = pressure_v[i];
	}
}


void simulate::Step2Pressure::generate_linear_equations_and_assign_pressure_to_node(
	nst::State& state
)
{
	const auto& [A, B] = generate_linear_equations(state);
	const auto& pressure_v = choose_method_of_solving_linear_equations(A, B);
	assign_pressure_v_to_each_node(state, pressure_v);
}
