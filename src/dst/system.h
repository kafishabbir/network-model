#ifndef DST_SYSTEM_H
#define DST_SYSTEM_H

#include "dst/parameter.h"
#include "dst/state.h"
#include "dst/measured.h"

//#include <eigen3/Eigen/Sparse>           // For SparseMatrix
#include <eigen3/Eigen/SparseCholesky>   // For SimplicialLLT
#include <eigen3/Eigen/IterativeLinearSolvers>
#include <fstream>

namespace dst
{
	class System
	{
	public:
		const Parameter parameter;
		State state;
		Measured measured;
		
		Eigen::SimplicialLLT<Eigen::SparseMatrix<double>> solver;
		Eigen::SparseMatrix<double> sparse_matrix;
		std::vector<int> id_nodes_unknown_pressure_v;
			
		Eigen::ConjugateGradient<Eigen::SparseMatrix<double>> iterative_solver;
		Eigen::VectorXd pressure_previous_solution;
		bool solver_initialized = false;
		bool has_previous_solution = false;

		System(const std::pair<Parameter, State>&);
		
		//REMOVE
		void print_matrix() const;
	};
}



#endif
