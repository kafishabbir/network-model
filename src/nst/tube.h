#ifndef NST_TUBE_H
#define NST_TUBE_H

#include "nst/tank.h"
#include <algorithm>

namespace nst
{
	class Tube
	{
	public:
		struct Calculated
		{
			double resistance_coefficient;
			double capillary_pressure_magnitude;
			double flow_rate;
			double velocity;
			double time;
			bool is_time_min;
			double length_displacement_p;
			double volume_displacement;
			int id_node_sink;
			nst::Tank tank_pour_into_node;
			double add_proportion;
			Calculated();
		};

		struct Visual
		{
			double radius;
			double length;
			std::vector<double> mpos;
		};

	public:
		int id_node_first;
		int id_node_second;
		double radius;
		double length;
		std::vector<double> mpos; //meniscus positions
		int id_fluid_first;

		Calculated calculated;
		Visual visual;

		Tube();
		double area() const;
		double volume() const;

		std::vector<double> mpos_long() const;

		Tube original() const;
		Tube reversed() const;
		void reverse();
	};

}

#endif
