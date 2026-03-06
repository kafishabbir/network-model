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
		Measure::total_fluid_in_system(system);
}

void simulate::Preparation::run(
	dst::System& system
)
{
	set_inlet_outlet_boundaries(system);
	
	create_connections_id_tube_v_for_node(system);
	
	assign_initial_total_fluid_to_system(system);
}
