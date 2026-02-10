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
		Tank();
		void add_fluid(const int fluid_id, const double volume);
		void fill_from_another_tank(const Tank& other);
		Tank return_sliced(const double volume) const;
		bool is_single_fluid() const;
		int id_single_fluid() const;

    };
}

#endif
