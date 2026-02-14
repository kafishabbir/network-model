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
		state.nodes[id_node_source].calculated.flow_out_id_tube_v.push_back(i);
	}
}


void simulate::Step6PourIntoNode::clear_node_tank(
	nst::State& state
)
{
	for(auto& node: state.nodes)
	{
		node.calculated.tank = nst::Tank();
		node.calculated.flow_out_id_tube_v.clear();
	}
}


std::vector<double> simulate::Step6PourIntoNode::mpos_long_until(
	const nst::Tube& tube,
	const double lp
)
{
	std::vector<double> mpos_new{0};
	for(const auto& x: tube.mpos)
	{
		if(x < lp)
		{
			mpos_new.push_back(x);
		}

	}
	mpos_new.push_back(lp);
	return mpos_new;
}


nst::Tank simulate::Step6PourIntoNode::produce_tank_with_fluids_flow_out_from_tube(
	const nst::Tube& tube
)
{
	const double lp = tube.calculated.length_displacement_p;
	const double volume_tube = tube.volume();

	nst::Tube tube_new = ((tube.calculated.velocity < 0) ? tube.original() : tube.reversed());
	const auto& mpos_long_sliced = mpos_long_until(tube_new, lp);

	nst::Tank tank;
	const int n_mpos_long_sliced = mpos_long_sliced.size();
	for(int i = 1; i < n_mpos_long_sliced; ++ i)
	{
		const int current_id_fluid = (tube_new.id_fluid_first + 1 + i) % 2;
		const double delta_lp = mpos_long_sliced[i] - mpos_long_sliced[i - 1];
		const double volume_fluid = volume_tube * delta_lp;

		tank.add_fluid(volume_fluid, current_id_fluid);
	}

	return tank;
}


void simulate::Step6PourIntoNode::assign_tank_to_tubes(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.tank_pour_into_node = produce_tank_with_fluids_flow_out_from_tube(tube);
	}
}


void simulate::Step6PourIntoNode::pour_from_tube_to_id_node_tank(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		const auto& tank_tube = tube.calculated.tank_pour_into_node;
		auto& tank_target = state.nodes[tube.calculated.id_node_sink].calculated.tank;
		tank_target.add_fluid(tank_tube);
	}
}


void simulate::Step6PourIntoNode::pour_from_tubes_to_node_tank(
	nst::State& state
)
{
	clear_node_tank(state);
	assign_id_node_id_tube_flow_direction(state);
	assign_tank_to_tubes(state);
	pour_from_tube_to_id_node_tank(state);
}
