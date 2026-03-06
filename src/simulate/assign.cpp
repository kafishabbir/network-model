#include "simulate/assign.h"

void simulate::Assign::assign_pressures_inlet(
	dst::System& system,
	const double pressure_inlet
)
{
	for(auto& node: system.state.nodes)
	{
		if(node.is_open_boundary && node.is_inlet)
		{
			node.pressure = pressure_inlet;
			node.is_pressure_known = true;
		}
	}
}

void simulate::Assign::assign_pressures_outlet(
	dst::System& system,
	const double pressure_outlet
)
{
	for(auto& node: system.state.nodes)
	{
		if(node.is_open_boundary && !node.is_inlet)
		{
			node.pressure = pressure_outlet;
			node.is_pressure_known = true;
		}
	}
}

void simulate::Assign::assign_pressures(
	dst::System& system,
	const double pressure_inlet,
	const double pressure_outlet
)
{
	assign_pressures_inlet(system, pressure_inlet);
	assign_pressures_outlet(system, pressure_outlet);
}


int simulate::Assign::find_type_fluid_contact(
	const int existing,
	const int addition
)
{
	if(existing == 2)
	{
		return 2;
	}
	if(existing == 0 && addition == 0)
	{
		return 0;
	}
	if(existing == 0 && addition == 1)
	{
		return 2;
	}
	if(existing == 1 && addition == 0)
	{
		return 2;
	}
	if(existing == 1 && addition == 1)
	{
		return 1;
	}
	if(existing == -1)
	{
		return addition;
	}
	
	throw std::invalid_argument("existing fluid in node not correct simulate::step::Part01Reference::find_type_fluid_contact()");
	return -1;
}

void simulate::Assign::assign_type_fluid_contact(
	dst::System& system
)
{
	for(auto& node: system.state.nodes)
	{
		node.calculated.type_fluid_contact = -1;
	}
	
	for(const auto& tube: system.state.tubes)
	{
		const int id_fluid_begin = tube.id_fluid_first;
		const int id_fluid_end = (tube.id_fluid_first + tube.mpos.size()) % 2;
		
		auto& contact_begin = system.state.nodes[tube.id_node_first].calculated.type_fluid_contact;
		auto& contact_end = system.state.nodes[tube.id_node_second].calculated.type_fluid_contact;
		
		contact_begin = find_type_fluid_contact(contact_begin, id_fluid_begin);
		contact_end = find_type_fluid_contact(contact_end, id_fluid_end);
	}
}
	
