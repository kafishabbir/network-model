#include "step/part09-displace.h"
#include <omp.h>

std::pair<int, std::vector<double>> step::Part09Displace::generate_tube_front(
	const double ap,
	const double lp
)
{
	int id_fluid_first = (ap < 1.0);

	if((ap > 0.0) && (ap < 1.0))
	{
		return {id_fluid_first, {(1.0 - ap) * lp}};
	}

	return {id_fluid_first, {}};
}

std::pair<int, std::vector<double>> step::Part09Displace::join_tubes(
	const std::pair<int, std::vector<double>>& tube_front,
	const std::pair<int, std::vector<double>>& tube_back,
	const double lp
)
{
	auto [id, mpos] = tube_front;
	const auto& [id_back, mpos_back] = tube_back;
	const int id_front_end = (id + mpos.size()) % 2;
	
	if(id_front_end != id_back)
	{
		mpos.push_back(lp);
	}
	// NUMERICAL-ERROR
	for(const double x: mpos_back)
	{
		const double x_add = x + lp;
		if(x_add < (1.0 - 1e-6))
		{
			mpos.push_back(x_add);
		}
		else
		{
			break;
		}
	}
	
	return {id, mpos};
}

std::pair<int, std::vector<double>> step::Part09Displace::generate_new_mpos_from_add_proportion(
	const nst::Tube& tube
)
{
	const bool is_reverse_needed = (tube.calculated.velocity < 0);
	const double lp = tube.calculated.length_displacement_p;
	const double ap = tube.calculated.add_proportion;

	const auto& tube_front = generate_tube_front(ap, lp);
	const auto& tube_back = tube.return_simple_tube_from_orientation(tube.calculated.velocity > 0);	
	const auto& joined = join_tubes(tube_front, tube_back, lp);

	if(is_reverse_needed)
	{
		return nst::Tube::tube_simple_reversed(joined);
	}

	return joined;
}

std::vector<double> step::Part09Displace::combine_swabs(
	const nst::Tube& tube
)
{
	const int n_mns = tube.mpos.size();
	const int id = tube.id_fluid_first;
	const int n_swabs = (n_mns - id) / 2;
	if(n_swabs < 2)
	{
		return tube.mpos;
	}

	double MX = 0;
	double M = 0;
	for(int i_swab = 0; i_swab < n_swabs; ++ i_swab)
	{
		const int begin = i_swab * 2 + id;
		const int end = begin + 1;
		const double x = tube.mpos[begin];
		const double y = tube.mpos[end];
		const double m = y - x;
		const double center = (y + x) / 2;
		MX += (center * m);
		M += m;
	}
	const double center = MX / M;
	const double x = center - M / 2;
	const double y = center + M / 2;
	const int begin = id;
	const int end = 2 * n_swabs + begin;

	auto v = tube.mpos;
	v.erase(v.begin() + begin, v.begin() + end);
	v.insert(v.begin() + begin, {x, y});
	return v;
}

void step::Part09Displace::generate_new_mpos_from_add_proportion(
	dst::System& system
)
{
	#pragma omp parallel for
	for(auto& tube: system.state.tubes)
	{
		const auto& [id, mpos] = generate_new_mpos_from_add_proportion(tube);
		tube.id_fluid_first = id;
		tube.mpos = mpos;
		tube.mpos = combine_swabs(tube);
	}
}
