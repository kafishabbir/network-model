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
		
	public:
		struct Calculated
		{
			double time_step;
			nst::Tank fluid_added;
			nst::Tank fluid_evacuated;
			
			// Fill these ones if I am saving a snap only
			nst::Tank fluid_in_system;
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
	
		nst::Nodes nodes;
		nst::Tubes tubes;
		
		Measured measured;
		
		Reference reference;
		Calculated calculated;
		
		State(const std::pair<nst::Nodes, nst::Tubes>&);
		
	};
	
	typedef std::vector<State> States;
}

#endif
