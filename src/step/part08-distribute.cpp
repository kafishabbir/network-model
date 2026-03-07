#include "step/part08-distribute.h"

void step::Part08Distribute::sort_id_tube_v_flow_out_at_node(
	dst::System& system
)
{
	for(auto& node: system.state.nodes)
	{
		auto& id_tube_v = node.calculated.flow_out_id_tube_v;
		std::vector<std::pair<double, int>> radius_id_tube_v;
		for(const int id_tube: id_tube_v)
		{
			const double radius = system.state.tubes[id_tube].radius;
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

void step::Part08Distribute::assign_proportion_to_tube(
	const std::vector<int>& flow_out_id_tube_v,
	const nst::Tank& tank,
	dst::System& system
)
{
	bool is_contain_water = tank.is_contain_water();
	double volume_water = tank.volume_water();

	for(const int id_tube: flow_out_id_tube_v)
	{
		auto& tube = system.state.tubes[id_tube];
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

void step::Part08Distribute::assign_proportion_to_tube(
	dst::System& system
)
{
	for(auto& node: system.state.nodes)
	{
		const auto& id_tube_v = node.calculated.flow_out_id_tube_v;
		const auto& node_tank = node.calculated.tank;
		assign_proportion_to_tube(id_tube_v, node_tank, system);
	}
}

void step::Part08Distribute::distribute_fluids_from_node_to_tube(
	dst::System& system
)
{
	sort_id_tube_v_flow_out_at_node(system);
	assign_proportion_to_tube(system);
	
	// NUMERICAL-ERROR
	for(auto& tube: system.state.tubes)
	{
		auto& x = tube.calculated.add_proportion;
		auto y = x;
		if(y > 1.0 || y < 0.0)
		{
			throw std::invalid_argument("length_proportion seriously incorrect");
		}
		if(1.0 - y < 1e-6)
		{
			x = 1.0;
		}
		else if(y < 1e-6)
		{
			x = 0.0;
		}
	}
}
