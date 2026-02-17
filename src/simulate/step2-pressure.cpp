#include "simulate/step2-pressure.h"

std::pair<dst::RowColVals, std::vector<double>> simulate::Step2Pressure::generate_symmetric_linear_equations(
	nst::State& state
)
{
	const int n_nodes = state.nodes.size();

	int count = 0;
	for(int i = 0; i < n_nodes; ++ i)
	{
		auto& node = state.nodes[i];
		if(node.is_open_boundary)
		{
			continue;
		}

		node.calculated.id_symmetric_solver = (count ++);
	}

	dst::RowColVals A;
	std::vector<double> B;

	for(int i = 0; i < n_nodes; ++ i)
	{
		const auto& node = state.nodes[i];
		if(node.is_open_boundary)
		{
			continue;
		}

		double val = 0;
		double b = 0;
		for(const int id_tube: node.reference.connections_id_tube_v)
		{
			const auto& tube = state.tubes[id_tube];

			const double sign = ((tube.id_node_first == i) ? 1 : -1);
			const int id_node_b = ((sign < 0) ? tube.id_node_first: tube.id_node_second);

			const double resistance = tube.calculated.resistance_coefficient;
			const double capillary_pressure =
				sign * tube.calculated.capillary_pressure_magnitude;

			val += resistance;
			if(state.nodes[id_node_b].is_open_boundary)
			{
				b += resistance * state.nodes[id_node_b].pressure;
			}
			else
			{
				A.push_back({node.calculated.id_symmetric_solver, state.nodes[id_node_b].calculated.id_symmetric_solver, -resistance});
			}

			b -= resistance * capillary_pressure;
		}
		B.push_back(b);
		A.push_back({node.calculated.id_symmetric_solver, node.calculated.id_symmetric_solver, val});
	}
	return {A, B};
}


void simulate::Step2Pressure::assign_symmetric_pressure_v_to_each_node(
	nst::State& state,
	const std::vector<double>& pressure_v
)
{

	const int n_nodes = state.nodes.size();
	int count = 0;
	for(int i = 0; i < n_nodes; ++ i)
	{
		auto& node = state.nodes[i];
		if(node.is_open_boundary)
		{
			node.calculated.pressure = node.pressure;
			continue;
		}
		node.calculated.pressure = pressure_v[count];
		++ count;
	}
}

void simulate::Step2Pressure::generate_symmetric_linear_equations_and_assign_pressure_to_node(
	nst::State& state,
	bool& is_solver_prepared,
	Eigen::SimplicialLLT<Eigen::SparseMatrix<double>>& solver
)
{
	const auto& [A, B] = generate_symmetric_linear_equations(state);
	//~ for(int i = 0; i < A.size(); ++ i)
	//~ {
		//~ auto [r, c, v] = A[i];
		//~ std::cout << i << ". (" << r << ", " << c << "), v="  << v << std::endl;
	//~ }

	//~ for(int i = 0; i < B.size(); ++ i)
	//~ {
		//~ std::cout << i << ". " << B[i] <<  std::endl;
	//~ }

	utility::Time time;
	const auto& pressure_v = choose_method_of_solving_linear_equations(A, B, is_solver_prepared, solver);
	state.measured.time_taken_by_solving_linear_equations += time.passed();
	std::cout << time.passed() << "\n";
	assign_symmetric_pressure_v_to_each_node(state, pressure_v);
}



std::vector<double> simulate::Step2Pressure::choose_method_of_solving_linear_equations(
	const dst::RowColVals& A,
	const std::vector<double>& B,
	bool& is_solver_prepared,
	Eigen::SimplicialLLT<Eigen::SparseMatrix<double>>& solver
)
{
	// return utility::Math::gaussian_elimination(A, B);
	// return utility::Math::eigen_no_symmetry_sparse_lu(A, B, B.size());
	return utility::Math::eigen_symmetry_cholesky(A, B, is_solver_prepared, solver);
}
