#ifndef SIMULATE_STEP1_PRESSURE_H
#define SIMULATE_STEP1_PRESSURE_H

#include "global/dst.h"
#include "simulate/physics.h"
#include "utility/math.h"

namespace simulate
{
    class Step1Pressure
    {
		static std::pair<global::Matrix, std::vector<double>> generate_linear_equations(
			const nst::State& state
		);

		static void assign_pressures_to_each_node(
			nst::Nodes& nodes,
			const std::vector<double>& pressures
		);

        public:

		static void solve_and_assign_pressure_at_nodes(
			nst::State& state
		);
    };
}

#endif
