#include "utility/math.h"

std::vector<double> utility::Math::gaussian_elimination(Matrix set_linear_equaitions)
{
	auto& v = set_linear_equaitions;
	const int n = set_linear_equaitions.size();

	for(int i = 0; i < n; ++ i)
	{
		auto& row = v[i];
		const double val = row[i];
		for(int j = 0; j <= n; ++ j)
		{
			row[j] /= val;
		}

		for(int j = 0; j < n; ++ j)
		{
			if(j == i)
			{
				continue;
			}

			auto& target_row = v[j];
			const double coeff = target_row[i];

			for(int k = 0; k <= n; ++ k)
			{
				target_row[k] -= coeff * row[k];
			}
		}
	}

	std::vector<double> ans(n);

	for(int i = 0; i < n; ++ i)
	{
		ans[i] = v[i].back();
	}

	return ans;
}
