#include "nst/tube.h"


std::vector<double> nst::Tube::mpos_long() const
{
	std::vector<double> v{0, 1};
	v.insert(v.begin() + 1, mpos.cbegin(), mpos.cend());
	return v;
}

std::vector<double> nst::Tube::mpos_long_displaced_scaled(
	const double p1,
	const double p2
) const
{
	auto v = mpos_long();
	const double length_effective = visual.length - p1 - p2;
	for(auto& x: v)
	{
		x = p1 + length_effective * x;
	}
	return v;
}

nst::Tube::Tube():
	id_node_first(-1),
	id_node_second(-1),
	radius(1),
	length(1),
	fluid_first(0)
{}

int nst::Tube::id_other_node(const int id_this_node) const
{
	if(id_this_node != id_node_first)
	{
		return id_node_first;
	}

	return id_node_second;
}


double nst::Tube::mu(const double mu1, const double mu2) const
{
	std::vector<double> muv{mu1, mu2};
	const auto& v = mpos_long();
	const int n = v.size();
	double sum = 0;
	for(int i = 1; i < n; ++ i)
	{
		double l = v[i] - v[i - 1];
		sum += l * muv[(i + 1) % 2];
	}

	return sum;
}

