#ifndef SIMULATE_STEP2_PRESSURE_H
#define SIMULATE_STEP2_PRESSURE_H

#include "global/dst.h"
#include "utility/math.h"

namespace simulate
{
    class Step2Pressure
    {
		static double determine_capillary_pressure_sign(
			const nst::Tube& tube,
			const int id_node_relative_to
		);

		static std::pair<dst::Matrix, std::vector<double>> generate_linear_equations(
			nst::State& state
		);

		static std::vector<double> choose_method_of_solving_linear_equations(
			const dst::Matrix& A, std::vector<double> B
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
