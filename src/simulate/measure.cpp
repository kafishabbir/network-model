#include "simulate/measure.h"

nst::Tank simulate::Measure::tube_inventory(const nst::Tube& tube)
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


nst::Tank simulate::Measure::fluid_in_system(const dst::System& system)
{
	nst::Tank tank;
	for(const auto& tube: system.state.tubes)
	{
		tank.add_fluid(tube_inventory(tube));
	}

	return tank;
}



