#include "step/part09-displace.h"

nst::Tube step::Part09Displace::generate_tube_front(
	const nst::Tube& tube,
	const double lp,
	const double ap
)
{
	nst::Tube tube_front(tube);
	if(ap == 1.0)
	{
		tube_front.id_fluid_first = 0;
	}
	else
	{
		tube_front.id_fluid_first = 1;
	}

	tube_front.mpos.clear();

	if((ap > 0.0) && (ap < 1.0))
	{
		tube_front.mpos.push_back((1.0 - ap) * lp);
	}

	return tube_front;
}

void step::Part09Displace::join_tubes(
	nst::Tube& tube_front,
	const nst::Tube& tube_back,
	const double lp
)
{
	const int id_fluid_tube_front_end = (tube_front.id_fluid_first + tube_front.mpos.size()) % 2;
	const int id_fluid_tube_back_begin = tube_back.id_fluid_first;

	if(id_fluid_tube_front_end != id_fluid_tube_back_begin)
	{
		tube_front.mpos.push_back(lp);
	}
	// NUMERICAL-ERROR
	for(const double x: tube_back.mpos)
	{
		const double x_add = x + lp;
		if(x_add < (1.0 - 1e-6))
		{
			tube_front.mpos.push_back(x_add);
		}
	}
}

nst::Tube step::Part09Displace::update_tube_mpos_according_to_proportion(
	const nst::Tube& tube
)
{
	const bool is_reverse_needed = (tube.calculated.velocity < 0);
	const double lp = tube.calculated.length_displacement_p;
	const double ap = tube.calculated.add_proportion;

	auto tube_front = generate_tube_front(tube, lp, ap);
	auto tube_back = (is_reverse_needed ? tube.reversed() : tube.original());
	join_tubes(tube_front, tube_back, lp);

	if(is_reverse_needed)
	{
		tube_front.reverse();
	}

	return tube_front;
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

void step::Part09Displace::update_tube_mpos_according_to_proportion(
	dst::System& system
)
{
	for(auto& tube: system.state.tubes)
	{
		tube = update_tube_mpos_according_to_proportion(tube);
		tube.mpos = combine_swabs(tube);
	}
}
