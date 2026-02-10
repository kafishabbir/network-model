#ifndef NST_TANK_H
#define NST_TANK_H

#include <vector>

namespace nst
{
    class Tank
    {
		struct FluidFlow
		{
			double volume = 0;
			bool has_flowed = false;
		};

		std::vector<FluidFlow> fluid_v;

        public:

		void add_fluid(const int fluid_id, const double volume);
		void fill_from_another_tank(const Tank& other);
		Tank();
    };
}

#endif
