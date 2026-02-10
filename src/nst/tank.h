#ifndef NST_TANK_H
#define NST_TANK_H

namespace nst
{
    class Tank
    {
		struct Fluid
		{
			double volume = 0;
			bool used = false;
		};

		std::vector<Fluid> fluid_v;

        public:

		void add_fluid(const int fluid_id, const double volume);
		Tank();
    };
}

#endif
