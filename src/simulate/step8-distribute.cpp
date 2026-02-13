#include "simulate/step8-distribute.h"

void simulate::Step8Distribute::sort_id_tube_v_flow_out_at_node(
	nst::State& state
)
{
	for(auto& node: state.nodes)
	{
		auto& id_tube_v = node.calculated.flow_out_id_tube_v;
		std::vector<std::pair<double, int>> radius_id_tube_v;
		for(const int id_tube: id_tube_v)
		{
			const double radius = state.tubes[id_tube].radius;
			radius_id_tube_v.push_back({radius, id_tube});
		}

		std::sort(radius_id_tube_v.begin(), radius_id_tube_v.end());

		std::vector<int> temp_id_tube_v;
		for(const auto& [radius, id_tube]: radius_id_tube_v)
		{
			temp_id_tube_v.push_back(id_tube);
		}

		id_tube_v = temp_id_tube_v;
	}
}

void simulate::Step8Distribute::assign_proportion_to_tube(
	const std::vector<int>& flow_out_id_tube_v,
	const nst::Tank& tank,
	nst::State& state
)
{
	bool is_contain_water = tank.is_contain_water();
	double volume_water = tank.volume_water();

	for(const int id_tube: flow_out_id_tube_v)
	{
		auto& tube = state.tubes[id_tube];
		auto& add_p = tube.calculated.add_proportion;
		const double capacity = tube.calculated.volume_displacement;

		if(tank.is_only_water())
		{
			add_p = 1.0;
		}
		else if(is_contain_water && (volume_water > capacity))
		{
			add_p = 1.0;
			volume_water -= capacity;
		}
		else if(is_contain_water)
		{
			add_p = volume_water / capacity;
			is_contain_water = false;
		}
		else
		{
			add_p = 0.0;
		}
	}
}

void simulate::Step8Distribute::assign_proportion_to_tube(
	nst::State& state
)
{
	for(auto& node: state.nodes)
	{
		const auto& id_tube_v = node.calculated.flow_out_id_tube_v;
		const auto& node_tank = node.calculated.tank;
		assign_proportion_to_tube(id_tube_v, node_tank, state);
	}
}



void simulate::Step8Distribute::distribute_fluids_from_node_to_tube(
	nst::State& state
)
{
	sort_id_tube_v_flow_out_at_node(state);
	assign_proportion_to_tube(state);
}
