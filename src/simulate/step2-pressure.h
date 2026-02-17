#ifndef SIMULATE_STEP2_PRESSURE_H
#define SIMULATE_STEP2_PRESSURE_H

#include "global/dst.h"
#include "utility/math.h"
#include "utility/time.h"

#include <vector>
#include <utility>


namespace simulate
{
    class Step2Pressure
    {
		static std::pair<dst::RowColVals, std::vector<double>> generate_symmetric_linear_equations(
			nst::State& state
		);


		static std::vector<double> choose_method_of_solving_linear_equations(
			const dst::RowColVals& A,
			const std::vector<double>& B,
			bool& is_solver_prepared,
			Eigen::SimplicialLLT<Eigen::SparseMatrix<double>>& solver
		);


		static void assign_symmetric_pressure_v_to_each_node(
			nst::State& state,
			const std::vector<double>& pressure_v
		);

        public:
		static void generate_symmetric_linear_equations_and_assign_pressure_to_node(
			nst::State& state,
			bool& is_solver_prepared,
			Eigen::SimplicialLLT<Eigen::SparseMatrix<double>>& solver
		);
    };
}

#endif
