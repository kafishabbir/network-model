#ifndef SIMULATE_SYSTEM_GENERATOR_H
#define SIMULATE_SYSTEM_GENERATOR_H

#include "dst/system.h"

namespace simulate
{
	class SystemGenerator
	{
		
		static std::pair<nst::Nodes, nst::Tubes> choose_network_geometry(
			const dst::Parameter& parameter
		);
		
		static int count_inlet_nodes(
			const dst::State& state
		);
		
		static dst::Parameter::GeometryDistributions::Distribution 
		find_distribution_radius(
			const dst::State& state
		);
		
		static dst::Parameter::GeometryDistributions::Distribution 
		find_distribution_length(
			const dst::State& state
		);
		
		static dst::Parameter::GeometryDistributions::Distribution 
		find_distribution_volume(
			const dst::State& state
		);
		
		static dst::Parameter parameter_processed(
			dst::Parameter parameter,
			const dst::State& state
		);
		
	public:
		static std::pair<dst::Parameter, dst::State> 
		generate_parameter_processed_and_basic_state(
			const dst::Parameter& parameter
		);
	};
}

#endif
