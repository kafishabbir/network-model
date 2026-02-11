#ifndef NST_TANK_H
#define NST_TANK_H

#include "global/decl.h"

namespace nst
{
    class Tank
    {
		struct Fluid
		{
			double volume;
			bool is_used = false;
			Fluid();
		};

		std::vector<Fluid> fluid_v;

	public:
		Tank();
		explicit Tank(const double volume, const int id_fluid);
		void add_fluid(const double volume, const int id_fluid);
		void add_fluid(const Tank& other);
		Tank return_sliced_tank(const double volume) const;
		bool is_only_water() const;
		double total_volume() const;

    };
}

#endif
