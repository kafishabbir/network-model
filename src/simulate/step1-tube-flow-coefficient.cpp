#include "simulate/step1-tube-flow-coefficient.h"

double simulate::Step1TubeFlowCoefficient::evaluate_mu(
	const nst::Tube& tube,
	const nst::State& state
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


double simulate::Step1TubeFlowCoefficient::resistance_coefficient(
	const nst::Tube& tube,
	const nst::State& state
)
{
	const double r = tube.radius;
	const double l = tube.length;
	const double mu = evaluate_mu(tube, state);
	return decl::pi / 8 * std::pow(r, 4) / mu / l;
}

double simulate::Step1TubeFlowCoefficient::capillary_pressure_magnitude(
	const nst::Tube& tube,
	const nst::State& state
)
{
	const double sign_id_fluid_first = ((tube.id_fluid_first == 0) ? 1 : -1);
	const double sign_n_meniscus = (tube.mpos.size() % 2);

	const double sigma = state.physical_constant.sigma;
	const double value_single_meniscus = 2.0 * sigma / tube.radius;

	return sign_id_fluid_first * sign_n_meniscus * value_single_meniscus;
}


void simulate::Step1TubeFlowCoefficient::capillary_pressure_magnitude(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.capillary_pressure_magnitude =
			capillary_pressure_magnitude(tube, state);
	}
}


void simulate::Step1TubeFlowCoefficient::resistance_coefficient(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.resistance_coefficient =
			resistance_coefficient(tube, state);
	}
}


void simulate::Step1TubeFlowCoefficient::assign_resistance_and_capillary_pressure_to_tubes(
	nst::State& state
)
{
	resistance_coefficient(state);
	capillary_pressure_magnitude(state);
}
