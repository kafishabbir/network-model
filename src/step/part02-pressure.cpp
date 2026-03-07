#include "step/part02-pressure.h"

step::Part02Pressure::Equation step::Part02Pressure::generate_equation_for_node(
	const int id_node,
	const dst::System& system
)
{
	Equation equation;
	equation.b = 0;
	
	const auto& node = system.state.nodes[id_node];
	double diag_val = 0;
	
	for(const int id_tube: node.reference.connections_id_tube_v)
	{
		const auto& tube = system.state.tubes[id_tube];
		
		const double sign = (tube.id_node_first == id_node) ? 1.0 : -1.0;
		const int id_node_b = (sign < 0) ? tube.id_node_first : tube.id_node_second;
		const auto& node_b = system.state.nodes[id_node_b];
		
		const double resistance = tube.calculated.resistance_coefficient;
		const double capillary_pressure =
			sign * tube.calculated.capillary_pressure_magnitude;
		
		diag_val += resistance;
		
		if(node_b.is_pressure_known)
		{
			equation.b += resistance * node_b.pressure;
		}
		else
		{
			equation.entry_v.push_back({node_b.reference.id_for_symmetric_matrix, -resistance});
		}
		
		equation.b -= resistance * capillary_pressure;
	}
	
	// It is obvious that the only open bounday is where there is const flow rate injection
	if(node.is_open_boundary)
	{
		equation.b += 1.0 / system.parameter.geometry.n_inject_boundaries;
	}
	
	equation.entry_v.push_back({node.reference.id_for_symmetric_matrix, diag_val});
	
	return equation;
}

void step::Part02Pressure::run(
	dst::System& system
)
{
	const int n_variables = system.id_nodes_unknown_pressure_v.size();
	Eigen::VectorXd b(n_variables);
	
	
	for(int i = 0; i < n_variables; ++ i)
	{
		const int id_node = system.id_nodes_unknown_pressure_v[i];
		const auto equation = generate_equation_for_node(id_node, system);
		
		for(const auto& [id_col, val] : equation.entry_v)
		{
			system.sparse_matrix.coeffRef(i, id_col) = val;
		}
		
		b(i) = equation.b;
	}
	
	// Factorize and solve
	system.solver.factorize(system.sparse_matrix);
	Eigen::VectorXd solution = system.solver.solve(b);
	
	if(system.solver.info() != Eigen::Success)
	{
		throw std::runtime_error("Part02Pressure: solving failed");
	}

	// Assign pressures back to nodes
	for(int i = 0; i < n_variables; ++ i)
	{
		const int id_node = system.id_nodes_unknown_pressure_v[i];
		system.state.nodes[id_node].calculated.pressure = solution(i);
	}
	
	for(auto& node: system.state.nodes)
	{
		if(node.is_pressure_known)
		{
			node.calculated.pressure = node.pressure;
		}
	}
}
