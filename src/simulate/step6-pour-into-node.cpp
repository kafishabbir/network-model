#include "simulate/step6-pour-into-node.h"


void simulate::Step6PourIntoNode::assign_id_node_id_tube_flow_direction(
	nst::State& state
)
{
	const int n_tubes = state.tubes.size();
	for(int i = 0; i < n_tubes; ++ i)
	{
		auto& tube = state.tubes[i];
		const double flow_rate = tube.calculated.flow_rate;
		int id_node_source = tube.id_node_first;
		int id_node_sink = tube.id_node_second;
		if(flow_rate < 0)
		{
			std::swap(id_node_source, id_node_sink);
		}

		tube.calculated.id_node_sink = id_node_sink;
		state.nodes[id_node_sink].calculated.flow_out_id_tube_v.push_back(i);
	}
}


void simulate::Step6PourIntoNode::clear_node_tank(
	nst::State& state
)
{
	for(auto& node: state.nodes)
	{
		node.calculated.tank = nst::Tank();
	}
}

void simulate::Step6PourIntoNode::pour_from_tube_to_id_node_tank(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		const int id_node_sink = tube.calculated.id_node_sink;
		state.nodes[id_node_sink].calculated.tank.add_fluid(tube.slice());
	}
}


void simulate::Step6PourIntoNode::pour_from_tubes_to_node_tank(
	nst::State& state
)
{
	assign_id_node_id_tube_flow_direction(state);
	clear_node_tank(state);
	pour_from_tube_to_id_node_tank(state);
}
