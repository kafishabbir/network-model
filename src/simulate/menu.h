#ifndef SIMULATE_MENU_H
#define SIMULATE_MENU_H

#include "dst/system.h"
#include "dst/system-output.h"

namespace simulate
{
    class Menu
    {
		static inline constexpr auto d = utility::Str::general;
	
	private:
	
        static bool inject_more_fluid(const dst::System& system);
        static void capture_this_state(dst::System& system);
        static void print_time_spent(double time_program, const dst::System& system);
        
    public:
        static dst::SystemOutput run(const dst::Parameter& parameter);
    };
}

#endif
