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


void simulate::Assign::update_node_contact_with_fluid(nst::Node& node, const int id_fluid_in_tube)
{
	if(id_fluid_in_tube == 0)
	{
		node.calculated.has_contact_with_water = true;
		return;
	}
	else if(id_fluid_in_tube == 1)
	{
		node.calculated.has_contact_with_oil = true;
		return;
	}		
	
	throw std::invalid_argument("id_fluid_in_tube, invalid, in updating node contact");
}

void simulate::Assign::assign_type_fluid_contact(
	dst::System& system
)
{
	for(auto& node: system.state.nodes)
	{
		node.calculated.has_contact_with_water = false;
		node.calculated.has_contact_with_oil = false;
	}
	
	for(const auto& tube: system.state.tubes)
	{
		const int id_fluid_begin = tube.id_fluid_first;
		const int id_fluid_end = (tube.id_fluid_first + tube.mpos.size()) % 2;
		
		
		auto& node_a = system.state.nodes[tube.id_node_first];
		auto& node_b = system.state.nodes[tube.id_node_second];
		
		
		update_node_contact_with_fluid(node_a, id_fluid_begin);
		update_node_contact_with_fluid(node_b, id_fluid_end);
	}
}
	
