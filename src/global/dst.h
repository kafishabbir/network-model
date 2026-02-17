#ifndef GLOBAL_DST_H
#define GLOBAL_DST_H

#include "nst/state.h"

#include <eigen3/Eigen/Sparse>
#include <eigen3/Eigen/SparseCholesky>
#include <eigen3/Eigen/SparseLU>

namespace dst
{
	typedef std::vector<nst::Node> Nodes;
	typedef std::vector<nst::State> States; // Sadly not the United States of America
	typedef std::vector<nst::Tube> Tubes;
	typedef std::vector<std::vector<double>> Matrix;
	typedef std::pair<std::string, std::string> str_pair;
	typedef std::tuple<int, int, double> row_col_val;
	typedef std::vector<row_col_val> RowColVals;
}

#endif
