#ifndef NST_STATE_H
#define NST_STATE_H

#include "nst/node.h"
#include "nst/tube.h"
#include "nst/fluid.h"

namespace nst
{
	class State
	{
		struct PhysicalConstant
		{
			double sigma;
			std::vector<nst::Fluid> fluid_v;
		};

		struct SimulationConstant
		{
			double time_step_resolution;
		};

		struct Calculated
		{
			double time_step;
		};


	public:
		PhysicalConstant physical_constant;
		SimulationConstant simulation_constant;

		std::vector<nst::Node> nodes;
		std::vector<nst::Tube> tubes;

		Calculated calculated;

		double fluid_zero_viscosity() const;
		double fluid_one_viscosity() const;
	};

}
#endif
