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
			PhysicalConstant();
		};

		struct SimulationConstant
		{
			double time_step_resolution;
			SimulationConstant();
		};

		struct Calculated
		{
			double time_step;
			int id_tube_time_min;
			nst::Tank fluid_added;
			nst::Tank fluid_evacuated;
			nst::Tank total_fluid_added;
			nst::Tank total_fluid_evacuated;
			Calculated();
		};


	public:
		PhysicalConstant physical_constant;
		SimulationConstant simulation_constant;

		std::vector<nst::Node> nodes;
		std::vector<nst::Tube> tubes;

		Calculated calculated;

		int id_step;

		State();
		double water_viscosity() const;
		double oil_viscosity() const;
	};

}
#endif
