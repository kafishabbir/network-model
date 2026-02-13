#ifndef SIMULATE_STEP2_PRESSURE_H
#define SIMULATE_STEP2_PRESSURE_H

#include "global/dst.h"
#include "utility/math.h"

namespace simulate
{
    class Step2Pressure
    {
		static std::pair<dst::Matrix, std::vector<double>> generate_linear_equations(
			const nst::State& state
		);

		static std::vector<double> choose_method_of_solving_linear_equations(
			const dst::Matrix& A, const std::vector<double>& B
		);

		static void assign_pressure_v_to_each_node(
			nst::State& state,
			const std::vector<double>& pressure_v
		);

        public:

        static void generate_linear_equations_and_assign_pressure_to_node(
			nst::State& state
		);
    };
}

#endif
