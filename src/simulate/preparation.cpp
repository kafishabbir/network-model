#include "simulate/preparation.h"

#include "simulate/measure.h"
#include "simulate/assign.h"
#include "ic/geometry-flow.h"

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
	
	
	const auto& [x_min, y_min, x_max, y_max] = ic::GeometryFlow::find_min_max_coordinates(system.state.nodes);
	const double L = y_max - y_min;
	const double omega_base = 2 * std::acos(-1) / L;
	const double omega_three_halfs = omega_base * 3.0 / 2.0;
	const double omega = omega_base * system.parameter.simulation.n_periods_of_initial_disturbance;

	
	const auto& nodes = system.state.nodes;
	auto& tubes = system.state.tubes;
	
	for(auto& tube: tubes)
	{
		const double x1 = nodes[tube.id_node_first].x;
		const double y1 = nodes[tube.id_node_first].y;
		const double x2 = nodes[tube.id_node_second].x;
		const double y2 = nodes[tube.id_node_second].y;
		const double x = (x1 + x2) / 2 - x_min;
		const double y = (y1 + y2) / 2 - y_min;
		
		const double x_func =
			2.0 / omega_three_halfs
			+ 1.0 / omega * std::cos(omega * (y - L / 2.0));
			
		if(x < x_func)
		{
			tube.id_fluid_first = system.parameter.simulation.id_fluid_inject;
			tube.mpos = {};
		}
	}
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
