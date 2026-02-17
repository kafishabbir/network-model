#include "utility/math.h"

std::vector<double> utility::Math::gaussian_elimination(
	dst::Matrix A,
	std::vector<double> B
)
{
    const int n = A.size();
    for(int i = 0; i < n; ++i)
    {
        auto& row = A[i];
        const double val = row[i];
        for(int j = 0; j < n; ++j)
        {
            row[j] /= val;
        }
		B[i] /= val;

        for(int j = 0; j < n; ++j)
        {
            if(j == i)
            {
                continue;
            }

            auto& target_row = A[j];
            const double coeff = target_row[i];

            for(int k = 0; k < n; ++k)
            {
                target_row[k] -= coeff * row[k];
            }

            B[j] -= coeff * B[i];
        }
    }

    return B;
}


dst::Matrix utility::Math::insert_row_col_val_into_full_matrix(
	const dst::RowColVals& row_col_val_v,
	const int n_variables
)
{
	dst::Matrix A(n_variables, std::vector<double>(n_variables));

	for(const auto& [row, col, val]: row_col_val_v)
	{
		A[row][col] = val;
	}

	return A;
}

std::vector<double> utility::Math::gaussian_elimination(
	const dst::RowColVals& row_col_val_v,
	const std::vector<double>& B
)
{
	const auto& A = insert_row_col_val_into_full_matrix(row_col_val_v, B.size());
	return gaussian_elimination(A, B);
}


std::vector<double> utility::Math::eigen_no_symmetry_sparse_lu(
    const dst::RowColVals& A_triplets,
    const std::vector<double>& B,
    int matrix_size
)
{
    const int n_triplets = A_triplets.size();
    std::vector<Eigen::Triplet<double>> triplet_list;
    triplet_list.reserve(n_triplets);

    for(int i = 0; i < n_triplets; ++ i)
    {
        const auto& [row, col, val] = A_triplets[i];
        triplet_list.push_back(Eigen::Triplet<double>(row, col, val));
    }

    Eigen::SparseMatrix<double> A(matrix_size, matrix_size);
    A.setFromTriplets(triplet_list.begin(), triplet_list.end());

    Eigen::VectorXd b = Eigen::Map<Eigen::VectorXd>(
        const_cast<double*>(B.data()), B.size()
    );

    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    solver.compute(A);

    if(solver.info() != Eigen::Success)
    {
        throw std::runtime_error("Sparse LU decomposition failed");
    }

    Eigen::VectorXd x = solver.solve(b);

    if(solver.info() != Eigen::Success)
    {
        throw std::runtime_error("Sparse LU solving failed");
    }

    std::vector<double> result(x.data(), x.data() + x.size());
    return result;
}


std::vector<double> utility::Math::eigen_symmetry_cholesky(
    const dst::RowColVals& row_col_val_v,
    const std::vector<double>& B,
    bool& is_solver_prepared,
    Eigen::SimplicialLLT<Eigen::SparseMatrix<double>>& solver  // Changed from CholmodSupernodalLLT
)
{
    const int n = B.size();

    // STEP 1: Convert your data to Eigen's triplet format
    std::vector<Eigen::Triplet<double>> triplets;
    triplets.reserve(row_col_val_v.size());
    for(const auto& [row, col, val]: row_col_val_v)
    {
        triplets.emplace_back(row, col, val);
    }

    // STEP 2: Build the sparse matrix
    Eigen::SparseMatrix<double> A(n, n);
    A.setFromTriplets(triplets.begin(), triplets.end());

    if(!is_solver_prepared)
    {
        // STEP 3: Analyze the sparsity pattern (expensive - do once)
        solver.analyzePattern(A);
        is_solver_prepared = true;
    }

    // STEP 4: Numerically factorize (do every time values change)
    solver.factorize(A);

    // Check if factorization succeeded (matrix must be SPD)
    if(solver.info() != Eigen::Success)
    {
        return std::vector<double>();
    }

    // STEP 5: Convert RHS and solve
    Eigen::VectorXd b(n);
    for(int i = 0; i < n; ++i)
    {
        b(i) = B[i];
    }

    Eigen::VectorXd x = solver.solve(b);

    // STEP 6: Convert back
    std::vector<double> result(n);
    for(int i = 0; i < n; ++i)
    {
        result[i] = x(i);
    }

    return result;
}
