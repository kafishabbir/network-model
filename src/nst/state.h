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

		struct Measured
		{
			double time_elapsed;
			nst::Tank total_fluid_added;
			nst::Tank total_fluid_evacuated;
			nst::Tank initial_total_fluid;
			double time_taken_by_solving_linear_equations;
			Measured();
		};

		struct Reference
		{
			int id_step;
			std::string comment;
			Reference();
		};

	public:
		struct Calculated
		{
			double time_step;
			nst::Tank fluid_added;
			nst::Tank fluid_evacuated;
			nst::Tank total_fluid_in_system;
			double saturation;
			double total_volume_delta;
			double water_volume_delta;
			double oil_volume_delta;
			Calculated();
		};

	public:
		PhysicalConstant physical_constant;
		SimulationConstant simulation_constant;

		std::vector<nst::Node> nodes;
		std::vector<nst::Tube> tubes;

		Measured measured;
		Reference reference;
		Calculated calculated;

		State();
		double water_viscosity() const;
		double oil_viscosity() const;
	};

}
#endif
