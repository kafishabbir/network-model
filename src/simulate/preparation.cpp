#include "simulate/preparation.h"

#include "simulate/measure.h"
#include "simulate/assign.h"

void simulate::Preparation::set_inlet_outlet_boundaries(
	dst::System& system
)
{	
	if(system.parameter.simulation.is_flow_const_flow_rate)
	{
		Assign::assign_pressures_outlet(system, 0.0);
		
	}
	else 
	{
		Assign::assign_pressures(
			system,
			system.parameter.simulation.inlet_pressure,
			0.0 
		);
	}
}

void simulate::Preparation::create_connections_id_tube_v_for_node(
	dst::System& system
)
{
	const int n_tubes = system.state.tubes.size();
	auto& nodes = system.state.nodes;
	
	for(int i = 0; i < n_tubes; ++i)
	{
		const auto& tube = system.state.tubes[i];
		const int id_node_first = tube.id_node_first;
		const int id_node_second = tube.id_node_second;

		nodes[id_node_first].reference.connections_id_tube_v.push_back(i);
		nodes[id_node_second].reference.connections_id_tube_v.push_back(i);
	}
}

void simulate::Preparation::assign_initial_total_fluid_to_system(
	dst::System& system
)
{		
	system.measured.initial_fluid = 
		Measure::fluid_in_system(system);
}

void simulate::Preparation::fill_system_initial_upto_certain_x(
	dst::System& system
)
{		
	if(!system.parameter.simulation.is_initially_filled)
	{
		return;
	}
	
	const auto& nodes = system.state.nodes;
	auto& tubes = 
	for(auto& tube: tubes)
	{
		const double x1 = nodes[tube.id_node_first].x;
		const double y1 = nodes[tube.id_node_first].y;
		const double x2 = nodes[tube.id_node_second].x;
		const double y2 = nodes[tube.id_node_second].y;
		double x = (x1 + x2) / 2 - x_center;
		const double y = (y1 + y2) / 2 - y_center;
		
		if(is_skewed)
		{
			x = x - 0.5 / n_periods * y;
		}
		
		tube.radius = 1.0 - constant_radius_contrast * std::cos(omega * x) * std::cos(omega * y);
	}

	double sum_radius_square = 0;
	for(const auto& tube: tubes)
	{
		sum_radius_square += std::pow(tube.radius, 2);
	}

	const double temp_radius_term = 1.0 / std::acos(-1) / constant_length_scale / sum_radius_square;
	const double coefficient_radius_scale = std::pow(temp_radius_term, 1.0 / 3);

	for(auto& tube: tubes)
	{
		tube.radius *= coefficient_radius_scale;
		tube.length = coefficient_radius_scale * constant_length_scale;
	}

	return {nodes, tubes};
	
}

void simulate::Preparation::run(
	dst::System& system
)
{
	
	fill_system_initial_upto_certain_x(system);
	
	set_inlet_outlet_boundaries(system);
	
	create_connections_id_tube_v_for_node(system);
	
	assign_initial_total_fluid_to_system(system);
}
