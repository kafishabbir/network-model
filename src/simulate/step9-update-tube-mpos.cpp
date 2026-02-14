#include "simulate/step9-update-tube-mpos.h"

nst::Tube simulate::Step9UpdateTubeMpos::generate_tube_front(
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

void simulate::Step9UpdateTubeMpos::join_tubes(
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

	for(const double x: tube_back.mpos)
	{
		const double x_add = x + lp;
		if(x_add < 1.0)
		{
			tube_front.mpos.push_back(x_add);
		}
	}
}

nst::Tube simulate::Step9UpdateTubeMpos::update_tube_mpos_according_to_proportion(
	const nst::Tube& tube
)
{
	const bool is_reverse_needed = (tube.calculated.velocity < 0);
	const double lp = tube.calculated.length_displacement_p;
	const double ap = tube.calculated.add_proportion;

	auto tube_front = generate_tube_front(tube, lp, ap);
	auto tube_back = (is_reverse_needed ? tube.reversed() :tube.original());
	join_tubes(tube_front, tube_back, lp);

	if(is_reverse_needed)
	{
		tube_front.reverse();
	}

	return tube_front;
}


void simulate::Step9UpdateTubeMpos::update_tube_mpos_according_to_proportion(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube = update_tube_mpos_according_to_proportion(tube);
	}

}
