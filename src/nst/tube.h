#ifndef NST_TUBE_H
#define NST_TUBE_H

#include "nst/tank.h"

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
	private:

		struct Calculated
		{
			double resistance_coefficient;
			double capillary_pressure_magnitude;
			double flow_rate;
			double velocity;
			double time;
			bool is_minimum_time;
			double length_displacement;
			double length_displacement_p;
			double volume_displacement;
			int id_node_pour;
			nst::Tank tank_pour_into_node;
			nst::Tank add_tank;
			bool is_locked_from_further_addition;
		};

		nst::Tube original() const;
		nst::Tube reversed() const;
		std::vector<double> mpos_long_until(const double lp_limit) const;

	public:
		int id_node_first;
		int id_node_second;
		double radius;
		double length;
		std::vector<double> mpos; //meniscus positions
		int fluid_first;

		Visual visual;
		Calculated calculated;

		Tube();

		double area() const;
		double volume() const;
		std::vector<double> mpos_long() const;

		std::vector<double> mpos_long_displaced_scaled(
			const double p1,
			const double p2
		) const;

		bool correct_direction(const int id_node_relative_to) const;
		int id_other_node(const int id_this_node) const;
		double mu(const double mu1, const double mu2) const;

		nst::Tank slice() const;

	};

}


#endif
