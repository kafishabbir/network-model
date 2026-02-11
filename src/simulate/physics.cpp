#include "simulate/physics.h"

double simulate::Physics::calculate_resistance(const nst::Tube& tube, const nst::State& state)
{
	const double r = tube.radius;
	const double l = tube.length;
	const double mu = tube.mu(state.water_viscosity(), state.oil_viscosity());
	return decl::pi / 8 * std::pow(r, 4) / mu / l;
}

double simulate::Physics::calculate_capillary_pressure_magnitude(
	const nst::Tube& tube,
	const nst::State& state
)
{
	const std::vector<int> sign_v{1, -1};
	const double cntrb_fluid_first = sign_v[tube.fluid_first];
	const double cntrb_n_meniscus = tube.mpos.size() % 2;

	const double two = 2;
	const double sigma = state.physical_constant.sigma;
	const double radius = tube.radius;
	const double value_single_meniscus = two * sigma / radius;

	return cntrb_fluid_first * cntrb_n_meniscus * value_single_meniscus;
}

double simulate::Physics::determine_capillary_pressure_sign(
	const nst::Tube& tube,
	const int id_node_relative_to
)
{
	return (
		tube.correct_direction(id_node_relative_to) ? 1 : -1
	);
}

