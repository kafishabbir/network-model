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
        for(int j = 0; j <= n; ++j)
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
