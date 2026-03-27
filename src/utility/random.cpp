#include "utility/random.h"

int utility::Random::integer_from_zero_until_n(const int n)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, n - 1);

	return dist(gen);
}


double utility::Random::rational_between_zero_and_one()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(0.0, 1.0);

	return dist(gen);
}
