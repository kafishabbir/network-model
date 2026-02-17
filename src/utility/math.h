#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include "global/dst.h"


namespace utility
{
	class Math
	{
		static std::vector<double> gaussian_elimination(
			const dst::Matrix A,
			const std::vector<double> B
		);

		static dst::Matrix insert_row_col_val_into_full_matrix(
			const dst::RowColVals& row_col_val_v,
			const int n_variables
		);

		public:

		static std::vector<double> gaussian_elimination(
			const dst::RowColVals& row_col_val_v,
			const std::vector<double>& B
		);


		static std::vector<double> eigen_no_symmetry_sparse_lu(
			const dst::RowColVals& A_triplets,
			const std::vector<double>& B,
			int matrix_size
		);

		static std::vector<double> eigen_symmetry_cholesky(
			const dst::RowColVals& row_col_val_v,
			const std::vector<double>& B,
			bool& is_solver_prepared,
			Eigen::SimplicialLLT<Eigen::SparseMatrix<double>>& solver  // Changed from CholmodSupernodalLLT
		);
	};
}

#endif
