#ifndef SIMULATE_MENU_H
#define SIMULATE_MENU_H

#include "io/file-write.h"


#include "simulate/step0-preparation.h"
#include "simulate/step1-tube-flow-coefficient.h"
#include "simulate/step2-pressure.h"
#include "simulate/step3-velocity.h"
#include "simulate/step4-time-step.h"
#include "simulate/step5-displacement.h"
#include "simulate/step6-pour-into-node.h"
#include "simulate/step7-inject-evacuate.h"
#include "simulate/step8-distribute.h"
#include "simulate/step9-update-tube-mpos.h"


namespace simulate
{
    class Menu
    {
        public:
		static void test_generate_and_plot();
    };
}

#endif
