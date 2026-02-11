#include "simulate/algorithm.h"

void simulate::Algorithm::unlock_all_tubes(
	nst::State& state,
	const std::vector<int>& flow_out_id_tube_v
)
{
	for (const int id_tube : flow_out_id_tube_v)
	{
		state.tubes[id_tube].calculated.is_locked = false;
	}
}

void simulate::Algorithm::distribute_water(
	nst::State& state,
	const std::vector<int>& flow_out_id_tube_v,
	nst::Tank& tank
)
{
	const double water_volume = tank.get_volume(0);
	if (water_volume <= 0.0) return;

	double remaining = water_volume;

	for (const int id_tube : flow_out_id_tube_v)
	{
		auto& tube = state.tubes[id_tube];
		const double capacity = tube.calculated.volume_displacement;
		const double volume = std::min(capacity, remaining);

		tube.calculated.tank.add_fluid(volume, 0);
		remaining -= volume;

		if (remaining <= 0.0) break;
	}

	tank.remove_fluid(water_volume - remaining, 0);
}

void simulate::Algorithm::distribute_oil(
	nst::State& state,
	const std::vector<int>& flow_out_id_tube_v,
	nst::Tank& tank
)
{
	const double oil_volume = tank.get_volume(1);
	if (oil_volume <= 0.0) return;

	double remaining = oil_volume;

	for (const int id_tube : flow_out_id_tube_v)
	{
		auto& tube = state.tubes[id_tube];
		const double capacity = tube.calculated.volume_displacement;
		const double volume = std::min(capacity, remaining);

		tube.calculated.tank.add_fluid(volume, 1);
		remaining -= volume;

		if (remaining <= 0.0) break;
	}

	tank.remove_fluid(oil_volume - remaining, 1);
}

std::pair<std::vector<double>, int> simulate::Algorithm::join_tank_to_tube(
	nst::Tube& tube,
	const nst::Tank& tank
)
{
	std::vector<double> meniscus_positions;
	meniscus_positions.clear();

	const double total_volume = tank.total_volume();
	if (total_volume <= 0.0)
	{
		return {meniscus_positions, 0};
	}

	double cumulative_volume = 0.0;
	int last_fluid_id = 0;

	for (const auto& [fluid_id, volume] : tank.get_contents())
	{
		cumulative_volume += volume;
		const double position = cumulative_volume / tube.cross_sectional_area();
		meniscus_positions.push_back(std::min(position, tube.length));
		last_fluid_id = fluid_id;
	}

	return {meniscus_positions, last_fluid_id};
}
```
