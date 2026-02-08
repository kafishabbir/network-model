#include "utility/math.h"

std::vector<double> utility::Math::gaussian_elimination(global::Matrix set_linear_equations)
{
    auto& v = set_linear_equations;
    const int n = set_linear_equations.size();

    for(int i = 0; i < n; ++i)
    {
        auto& row = v[i];
        const double val = row[i];
        for(int j = 0; j <= n; ++j)
        {
            row[j] /= val;
        }

        for(int j = 0; j < n; ++j)
        {
            if(j == i)
            {
                continue;
            }

            auto& target_row = v[j];
            const double coeff = target_row[i];

            for(int k = 0; k <= n; ++k)
            {
                target_row[k] -= coeff * row[k];
            }
        }
    }

    std::vector<double> ans(n);
    for(int i = 0; i < n; ++i)
    {
        ans[i] = v[i].back();
    }

    return ans;
}

std::vector<double> utility::Math::jacobi_method(global::Matrix augmented_matrix,
                                                 int max_iterations,
                                                 double tolerance)
{
    const int n = augmented_matrix.size();
    std::vector<double> x(n, 0.0);  // Initial guess (all zeros)
    std::vector<double> x_new(n, 0.0);

    // Extract coefficient matrix A and vector b from augmented matrix
    global::Matrix A(n, std::vector<double>(n));
    std::vector<double> b(n);

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            A[i][j] = augmented_matrix[i][j];
        }
        b[i] = augmented_matrix[i][n];
    }

    for(int iter = 0; iter < max_iterations; ++iter)
    {
        for(int i = 0; i < n; ++i)
        {
            double sum = 0.0;
            for(int j = 0; j < n; ++j)
            {
                if(j != i)
                {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        // Check convergence
        double max_diff = 0.0;
        for(int i = 0; i < n; ++i)
        {
            max_diff = std::max(max_diff, std::abs(x_new[i] - x[i]));
        }

        x = x_new;

        if(max_diff < tolerance)
        {
            std::cout << "Jacobi converged in " << iter + 1 << " iterations\n";
            break;
        }
    }

    return x;
}

std::vector<double> utility::Math::gauss_seidel_method(global::Matrix augmented_matrix,
                                                       int max_iterations,
                                                       double tolerance)
{
    const int n = augmented_matrix.size();
    std::vector<double> x(n, 0.0);  // Initial guess

    // Extract coefficient matrix A and vector b from augmented matrix
    global::Matrix A(n, std::vector<double>(n));
    std::vector<double> b(n);

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            A[i][j] = augmented_matrix[i][j];
        }
        b[i] = augmented_matrix[i][n];
    }

    for(int iter = 0; iter < max_iterations; ++iter)
    {
        std::vector<double> x_old = x;

        for(int i = 0; i < n; ++i)
        {
            double sum = 0.0;
            for(int j = 0; j < n; ++j)
            {
                if(j != i)
                {
                    sum += A[i][j] * x[j];
                }
            }
            x[i] = (b[i] - sum) / A[i][i];
        }

        // Check convergence
        double max_diff = 0.0;
        for(int i = 0; i < n; ++i)
        {
            max_diff = std::max(max_diff, std::abs(x[i] - x_old[i]));
        }

        if(max_diff < tolerance)
        {
            std::cout << "Gauss-Seidel converged in " << iter + 1 << " iterations\n";
            break;
        }
    }

    return x;
}
