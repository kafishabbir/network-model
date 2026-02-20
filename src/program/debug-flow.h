#ifndef PROGRAM_DEBUG_FLOW_H
#define PROGRAM_DEBUG_FLOW_H

#include "simulate/menu.h"

namespace program
{
    class DebugFlow
    {
		static visualize::Property generate_visual_property();
		static simulate::Property generate_property();

        public:
		static void run();

    };
}

#endif
