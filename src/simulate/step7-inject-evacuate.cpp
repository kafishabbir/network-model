#include "simulate/step7-inject-evacuate.h"

nst::Tank simulate::Step7InjectEvacuate::produce_tank_with_oil_sliced_out(
	const nst::Tank& tank,
	const double volume
)
{
	if(volume < 0)
	{
        throw std::invalid_argument("Volume must be positive");
    }
    if(tank.total_volume() < volume)
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
		const double need_to_add = volume - tank_new.total_volume();
		tank_new.add_fluid(need_to_add, 0);
	}

	return tank_new;
}


void simulate::Step7InjectEvacuate::assign_volume_flow_out_to_node(
	nst::State& state
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


void simulate::Step7InjectEvacuate::balance_flow_at_open_nodes(
	nst::State& state
)
{
	auto& addition_tank = state.calculated.fluid_added;
	addition_tank = nst::Tank();
	auto& evacuation_tank = state.calculated.fluid_evacuated;
	evacuation_tank = nst::Tank();

	for(auto& node: state.nodes)
	{
		if(!node.is_open_boundary)
		{
			continue;
		}
		auto& node_tank = node.calculated.tank;

		const double flow_in_total = node_tank.total_volume();
		const double flow_out_total = node.calculated.volume_fluid_flow_out;
		const double delta_volume = std::abs(flow_in_total - flow_out_total);

		if(flow_in_total < flow_out_total)
		{
			// add
			const int id_fluid = node.id_fluid_inject;
			node_tank.add_fluid(delta_volume, id_fluid);
			addition_tank.add_fluid(delta_volume, id_fluid);
			node.calculated.is_fluid_added_to_this_node = true;
		}
		else
		{
			//evacualate
			const auto& tank_with_oil_sliced_out =
				produce_tank_with_oil_sliced_out(node_tank, delta_volume);

			evacuation_tank.add_fluid(tank_with_oil_sliced_out);
			node.calculated.is_fluid_added_to_this_node = false;
		}
	}

	state.calculated.total_fluid_added.add_fluid(addition_tank);
	state.calculated.total_fluid_evacuated.add_fluid(evacuation_tank);
}


void simulate::Step7InjectEvacuate::inject_and_evacuate_fluid_from_system(
	nst::State& state
)
{
	assign_volume_flow_out_to_node(state);
	balance_flow_at_open_nodes(state);
}
