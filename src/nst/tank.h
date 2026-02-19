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
			bool is_used;
			Fluid();
		};

		std::vector<Fluid> fluid_v;

	public:
		Tank();

		void add_fluid(const double volume, const int id_fluid);
		void add_fluid(const Tank& other);

		bool is_only_water() const;
		bool is_contain_water() const;
		bool is_contain_oil() const;

		double volume_water() const;
		double volume_oil() const;
		double volume_total() const;

    };
}

#endif
