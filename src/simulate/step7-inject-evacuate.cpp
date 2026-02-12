#include "simulate/step7-inject-evacuate.h"

void simulate::Step7InjectEvacuate::assign_volume_flow_out_to_node(
	nst::State& state
)
{
	for(auto& node: state.nodes)
	{
		auto& volume = node.calculated.volume_fluid_flow_out;
		volume = 0;
		for(const int id_tube: node.flow_out_id_tube_v)
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
			const int id_fluid = node.fluid_to_input;
			node_tank.add_fluid(delta_volume, id_fluid);
			addition_tank.add_fluid(delta_volume, id_fluid);
			node.calculated.is_fluid_added_to_this_node = true;
		}
		else
		{
			//evacualate
			evacuation_tank.add_fluid(node_tank.slice(delta_volume);
			node.calculated.is_fluid_added_to_this_node  = false;
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
