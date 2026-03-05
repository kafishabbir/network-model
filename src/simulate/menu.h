#ifndef SIMULATE_MENU_H
#define SIMULATE_MENU_H

#include "simulate/property.h"
#include "dst/system.h"


namespace simulate
{
	class Menu
	{
		static inline constexpr auto d = utility::Str::general;
		

	public:
		static dst::System run(const dst::Parameter& parameter);
	};
}

#endif
