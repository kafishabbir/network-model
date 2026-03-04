#ifndef DST_STATE_H
#define DST_STATE_H

#include "nst/node.h"
#include "nst/tube.h"

namespace dst
{
	class State
	{
		struct Measured
		{
			double time_elapsed;
			double time_taken_by_solving_linear_equations;
			std::vector<double> time_taken_by_each_step;
			
			nst::Tank fluid_added;
			nst::Tank fluid_evacuated;
			
			Measured();
		};
		
		struct Reference
		{
			int id_step;
			std::string comment;
		
			Reference();
		};
		
		struct Calculated
		{
			double time_step;
			nst::Tank fluid_added;
			nst::Tank fluid_evacuated;
			
			// Fill these ones if I am saving a snap only
			nst::Tank total_fluid_in_system;
			double saturation;
			double volume_total_delta;
			double water_volume_delta;
			double oil_volume_delta;
			double average_pressure;
			std::vector<std::pair<double, double>> pressure_vs_y;
			std::vector<std::pair<double, double>> saturation_vs_x;
			Calculated();
		};
		
	public:
		
		Measured measured;
		
		nst::Nodes nodes;
		nst::Tubes tubes;
		
		Reference reference;
		Calculated calculated;
		
	};
	
	typedef std::vector<State> States;
}

#endif
