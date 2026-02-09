#ifndef NST_TUBE_H
#define NST_TUBE_H

#include <vector>
namespace nst
{
	class Tube
	{


	public:
		struct Visual
		{
			double radius;
			double length;
			std::vector<double> mpos;
		};

		struct Calculated
		{
			double flow_rate;
		};

		int id_node_first;
		int id_node_second;
		double radius;
		double length;
		std::vector<double> mpos; //meniscus positions
		int fluid_first;

		Calculated calculated;
		Visual visual;
		Tube();

		std::vector<double> mpos_long() const;

		std::vector<double> mpos_long_displaced_scaled(
			const double p1,
			const double p2
		) const;

		int id_other_node(const int id_this_node) const;
		double mu(const double mu1, const double mu2) const;
	};

}


#endif
