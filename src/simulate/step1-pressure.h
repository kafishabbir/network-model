#ifndef SIMULATE_STEP1_PRESSURE_H
#define SIMULATE_STEP1_PRESSURE_H

#include "simulate/step-preparation.h"
#include "utility/math.h"

namespace simulate
{
    class Step1Pressure
    {
		static std::pair<dst::Matrix, std::vector<double>> generate_linear_equations(
			const nst::State& state
		);

		static void assign_pressures_to_each_node(
			dst::Nodes& nodes,
			const std::vector<double>& pressures
		);

        public:

		static void solve_and_assign_pressure_at_nodes(
			nst::State& state
		);
    };
}

#endif
