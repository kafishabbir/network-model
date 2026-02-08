#include "simulate/physics.h"

double simulate::Physics::calculate_a(const nst::Tube& tube, const nst::State& state)
{
	const double r = tube.radius;
	const double l = tube.length;
	const double pi = std::acos(-1);
	const double mu = tube.mu(state.mu1, state.mu2);
	return  pi / 8 * std::pow(r, 4) / mu / l;
}

