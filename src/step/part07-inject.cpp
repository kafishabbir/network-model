#include "step/part07-inject.h"

nst::Tank step::Part07Inject::produce_tank_with_oil_sliced_out(
	const nst::Tank& tank,
	const double volume
)
{
	if(volume < 0)
	{
		throw std::invalid_argument("Volume must be positive");
	}
	if(tank.volume_total() < volume)
	{
		throw std::runtime_error("Insufficient volume in tank to slice");
	}

	nst::Tank tank_new;

	if(tank.is_contain_oil())
	{
		if(tank.volume_oil() >= volume)
		{
			tank_new.add_fluid(volume, 1);
			return tank_new;
		}
		tank_new.add_fluid(tank.volume_oil(), 1);
	}
	if(tank.is_contain_water())
	{
		const double need_to_add = volume - tank_new.volume_total();
		tank_new.add_fluid(need_to_add, 0);
	}

	return tank_new;
}


void step::Part07Inject::assign_volume_flow_out_to_node(
	dst::System& system
)
{
	for(auto& node: state.nodes)
	{
		auto& volume = node.calculated.volume_fluid_flow_out;
		volume = 0;
		for(const int id_tube: node.calculated.flow_out_id_tube_v)
		{
			const auto& tube = state.tubes[id_tube];
			volume += tube.calculated.volume_displacement;
		}
	}
}


void step::Part07Inject::balance_flow_at_open_nodes(
	dst::System& system
)
{
	auto& addition_tank = state.calculated.fluid_added;
	auto& evacuation_tank = state.calculated.fluid_evacuated;

	for(auto& node: state.nodes)
	{
		if(!node.is_open_boundary)
		{
			continue;
		}
		auto& node_tank = node.calculated.tank;

		const double flow_in_total = node_tank.volume_total();
		const double flow_out_total = node.calculated.volume_fluid_flow_out;
		const double delta_volume = std::abs(flow_in_total - flow_out_total);

		if(flow_in_total < flow_out_total)
		{
			// add
			const int id_fluid = node.id_fluid_inject;
			node_tank.add_fluid(delta_volume, id_fluid);
			addition_tank.add_fluid(delta_volume, id_fluid);
			node.calculated.is_fluid_injected_from_external_to_this_node = true;
		}
		else
		{
			//evacualate
			const auto& tank_with_oil_sliced_out =
				produce_tank_with_oil_sliced_out(node_tank, delta_volume);
			evacuation_tank.add_fluid(tank_with_oil_sliced_out);
			node.calculated.is_fluid_injected_from_external_to_this_node = false;
		}
	}

	state.measured.total_fluid_added.add_fluid(addition_tank);
	state.measured.total_fluid_evacuated.add_fluid(evacuation_tank);
}


void step::Part07Inject::inject_and_evacuate_fluid_from_system(
	dst::System& system
)
{
	assign_volume_flow_out_to_node(state);
	balance_flow_at_open_nodes(state);
}
