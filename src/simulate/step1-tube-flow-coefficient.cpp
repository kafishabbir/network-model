#include "simulate/step1-tube-flow-coefficient.h"

double simulate::Step1TubeFlowCoefficient::resistance_coefficient(
	const nst::Tube& tube,
	const nst::State& state
)
{
	const double r = tube.radius;
	const double l = tube.length;
	const double mu = tube.mu(state.water_viscosity(), state.oil_viscosity());
	return decl::pi / 8 * std::pow(r, 4) / mu / l;
}

double simulate::Step1TubeFlowCoefficient::capillary_pressure_magnitude(
	const nst::Tube& tube,
	const nst::State& state
)
{
	const std::vector<int> sign_v{1, -1};
	const double cntrb_fluid_first = sign_v[tube.fluid_first];
	const double cntrb_n_meniscus = tube.mpos.size() % 2;

	const double sigma = state.physical_constant.sigma;
	const double radius = tube.radius;
	const double value_single_meniscus = 2.0 * sigma / radius;

	return cntrb_fluid_first * cntrb_n_meniscus * value_single_meniscus;
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
