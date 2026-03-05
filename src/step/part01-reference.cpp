#include "step/part01-reference.h"
#include "simulate/utility.h"

double step::Part01Reference::evaluate_mu(
	const nst::Tube& tube,
	const dst::System& system
)
{
	std::vector<double> mu_v{state.water_viscosity(), state.oil_viscosity()};
	const auto& mpos_long = tube.mpos_long();
	const int n = mpos_long.size();
	double sum = 0;
	for(int i = 1; i < n; ++ i)
	{
		sum += (mpos_long[i] - mpos_long[i - 1]) * mu_v[(i + 1) % 2];
	}

	return sum;
}


double step::Part01Reference::resistance_coefficient(
	const nst::Tube& tube,
	const dst::System& system
)
{
	const double r = tube.radius;
	const double l = tube.length;
	const double mu = evaluate_mu(tube, state);
	return std::acos(-1) / 8 * std::pow(r, 4) / mu / l;
}

double step::Part01Reference::capillary_pressure_magnitude(
	const nst::Tube& tube,
	const dst::System& system
)
{
	const double sign_id_fluid_first = ((tube.id_fluid_first == 0) ? 1 : -1);
	const double sign_n_meniscus = (tube.mpos.size() % 2);

	const double sigma = state.physical_constant.sigma;
	const double value_single_meniscus = 2.0 * sigma / tube.radius;

	return sign_id_fluid_first * sign_n_meniscus * value_single_meniscus;
}


void step::Part01Reference::capillary_pressure_magnitude(
	dst::System& system
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.capillary_pressure_magnitude =
			capillary_pressure_magnitude(tube, state);
	}
}


void step::Part01Reference::resistance_coefficient(
	dst::System& system
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.resistance_coefficient =
			resistance_coefficient(tube, state);
	}
}

void step::Part01Reference::reset_calculated(dst::System& system)
{
	state.calculated = nst::State::Calculated();
	for(auto& node: state.nodes)
	{
		node.calculated = nst::Node::Calculated();
	}
	for(auto& tube: state.tubes)
	{
		tube.calculated = nst::Tube::Calculated();
	}
}


void step::Part01Reference::assign_resistance_and_capillary_pressure_to_tubes(
	dst::System& system
)
{
	reset_calculated(state);
	resistance_coefficient(state);
	capillary_pressure_magnitude(state);
	simulate::Utility::assign_type_fluid_contact(state);
}

