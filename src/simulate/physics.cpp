#include "simulate/physics.h"

double simulate::Physics::calculate_resistance(const nst::Tube& tube, const nst::State& state)
{
	const double r = tube.radius;
	const double l = tube.length;
	const double mu = tube.mu(state.mu1, state.mu2);
	return decl::pi / 8 * std::pow(r, 4) / mu / l;
}

double simulate::Physics::calculate_laplace_pressure_value(
	const nst::Tube& tube,
	const nst::State& state
)
{
	const double two = 2;
	const double sigma = state.sigma;
	const double radius = tube.radius;
	return two * sigma / radius;
}

double simulate::Physics::calculate_laplace_pressure_sign(
	const nst::Tube& tube,
	const int node_id_relative_to
)
{
	const std::vector<int> sign_v{1, -1};

	const int direction_int = tube.correct_direction(node_id_relative_to);

	const double cntrb_n_meniscus = tube.mpos.size() % 2;
	const double cntrb_fluid_first = sign_v[tube.fluid_first];
	const double cntrb_direction = sign_v[direction_int];

	return cntrb_n_meniscus * cntrb_fluid_first * cntrb_direction;
}


double simulate::Physics::calculate_laplace_pressure(
	const nst::Tube& tube,
	const nst::State& state,
	const int node_id_relative_to
)
{
	const double sign = calculate_laplace_pressure_sign(
		tube, node_id_relative_to
	);

	const double value = calculate_laplace_pressure_value(
		tube, state
	);
	return sign * value;
}


