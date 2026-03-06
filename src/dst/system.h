#ifndef DST_SYSTEM_H
#define DST_SYSTEM_H

#include "dst/parameter.h"
#include "dst/state.h"
#include "dst/measured.h"

//#include <eigen3/Eigen/Sparse>           // For SparseMatrix
#include <eigen3/Eigen/SparseCholesky>   // For SimplicialLLT

namespace dst
{
	class System
	{
	public:
		const Parameter parameter;
		State state;
		Measured measured;
		Eigen::SimplicialLLT<Eigen::SparseMatrix<double>> solver;
		
		System(const std::pair<Parameter, State>&);
	};
}

#endif
