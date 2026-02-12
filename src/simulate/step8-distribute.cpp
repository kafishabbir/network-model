#include "simulate/step8-distribute.h"


void simulate::Step8Distribute::sort_id_tube_v_flow_out_at_node(
	nst::State& state
)
{
}


void simulate::Step8Distribute::assign_proportion_to_tube(
	nst::State& state
)
{
	void simulate::Algorithm::distribute(
	nst::State& state,
	const std::vector<int>& flow_out_id_tube_v,
	const nst::Tank& tank
)
{
	double volume_water = tank.volume_water();
	for(const int id_tube: flow_out_id_tube_v)
	{
		auto& tube = state.tubes[id_tube];
		auto& add_p = tube.calculated.add_proportion;
		const double capacity = tube.claculated.volume_displacement;
		if(tank.is_only_water())
		{
			add_p = 1.0;
		}
		else if((volume_water > 0.0) && (volume_water > capacity))
		{
			add_p  = 1.0;
			volume_water -= capacity;
		}
		else if(volume_water > 0.0)
		{
			add_p = volume_water / capacity;
			volume_water = 0.0;
		}
		else
		{
			add_p = 0.0
		}
	}
}



void simulate::Step8Distribute::update_tube_mpos_according_to_proportion(
	nst::State& state
)
{
}


void simulate::Step8Distribute::distribute_fluids_from_node_to_tube(
	nst::State& state
)
{
	sort_id_tube_v_flow_out_at_node(state);
	assign_proportion_to_tube(state);
	update_tube_mpos_according_to_proportion(state);
}
