




#include "simulate/measure.h"
void simulate::Measure::blank()
{

}






#include "simulate/utility.h"

void simulate::Utility::assign_pressure(
	dst::System& system,
	const double pressure_left_boundary,
	const double pressure_right_boundary
)
{
	for(auto& node: state.nodes)
	{
		if(node.is_open_boundary)
		{
			if(node.is_inlet)
			{
				node.pressure = pressure_left_boundary;
			}
			else
			{
				node.pressure = pressure_right_boundary;
			}
		}
	}


}

nst::Tank simulate::Utility::tube_inventory(const nst::Tube& tube)
{
	const auto& v = tube.mpos_long();
	const int n = v.size();
	const double vol = tube.volume();
	nst::Tank tank;
	for(int i = 1; i < n; ++ i)
	{
		const int id_fluid = (tube.id_fluid_first + 1 + i) % 2;
		const double l = v[i] - v[i - 1];
		tank.add_fluid(vol * l, id_fluid);
	}

	return tank;
}


nst::Tank simulate::Utility::total_fluid_in_system(const dst::System& system)
{
	nst::Tank tank;
	for(const auto& tube: state.tubes)
	{
		tank.add_fluid(tube_inventory(tube));
	}

	return tank;
}



int simulate::Utility::find_type_fluid_contact(
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

void simulate::Utility::assign_type_fluid_contact(
	dst::System& system
)
{
	for(auto& node: state.nodes)
	{
		node.calculated.type_fluid_contact = -1;
	}
	
	for(const auto& tube: state.tubes)
	{
		const int id_fluid_begin = tube.id_fluid_first;
		const int id_fluid_end = (tube.id_fluid_first + tube.mpos.size()) % 2;
		
		auto& contact_begin = state.nodes[tube.id_node_first].calculated.type_fluid_contact;
		auto& contact_end = state.nodes[tube.id_node_second].calculated.type_fluid_contact;
		
		contact_begin = find_type_fluid_contact(contact_begin, id_fluid_begin);
		contact_end = find_type_fluid_contact(contact_end, id_fluid_end);
	}
}
	
