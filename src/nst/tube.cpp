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
	return (correct_direction(id_this_node) ? id_node_second : id_node_first);
}

double nst::Tube::mu(const double mu1, const double mu2) const
{
	std::vector<double> mu_v{mu1, mu2};
	const auto& v = mpos_long();
	const int n = v.size();
	double sum = 0;
	for(int i = 1; i < n; ++ i)
	{
		const double l = v[i] - v[i - 1];
		sum += l * mu_v[(i + 1) % 2];
	}

	return sum;
}
std::vector<double> nst::Tube::mpos_long_until(const double lp_limit) const
{
	const auto& v = mpos_long();
	std::vector<double> w;
	for(const auto& x: v)
	{
		if(x >= lp_limit)
		{
			break;
		}
		w.push_back(x);
	}

	w.push_back(lp_limit);
	return w;
}

bool nst::Tube::correct_direction(const int id_node_relative_to) const
{
	return id_node_first == id_node_relative_to;
}

nst::Tube nst::Tube::original() const
{
	return *this;
}

nst::Tube nst::Tube::reversed() const
{
	nst::Tube tube = *this;
	for(auto& x: tube.mpos)
	{
		x = 1.0 - x;
	}
	tube.fluid_first = (tube.fluid_first + tube.mpos.size()) % 2;

	return tube;
}

nst::Tank nst::Tube::slice(const double time_step) const
{
	const double lp = calculated.length_unit_less_displacement;
	const double volume_tube = decl::pi * std::pow(radius, 2) * length;

	Tube tube = ((calculated.velocity < 0) ? original() : reversed());

	const auto& mpos_long_sliced = tube.mpos_long_until(lp);

	const int n_mpos_long_sliced = mpos_long_sliced.size();
	nst::Tank tank;
	for(int i = 1; i < n_mpos_long_sliced; ++ i)
	{
		const int current_fluid_id = (tube.fluid_first + 1 + i) % 2;
		const double delta_lp = mpos_long_sliced[i] - mpos_long_sliced[i - 1];
		const double volume_fluid = volume_tube * delta_lp;
		tank.add_fluid(current_fluid_id, volume_fluid);
	}

	return tank;
}
