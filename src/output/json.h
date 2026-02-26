#ifndef OUTPUT_JSON_H
#define OUTPUT_JSON_H

#include <vector>
#include <string>

namespace output
{
	struct Json
	{
		class Simulation
		{
			struct InitialParameter
			{
				int id_fluid_inject;
				double sigma;
				double viscosity_ratio;
				double radius_contrast;
				int n_tube_rows;
				int n_tube_cols;
				double n_periods;
			};
			
			struct NetworkProperty
			{
				int n_tubes;
				int n_nodes;
				double radius_average;
				double radius_min;
				double radius_max;
				double radius_ratio;
				double length_average;
				double length_min;
				double length_max;
				double length_ratio;
			};
		public:	
			struct Capture
			{
				double time;
				std::vector<std::pair<double, double>> pressure_vs_y;
				std::vector<std::pair<double, double>> saturation_vs_x;
			};
			
		
			int id;
			InitialParameter initial_parameter;
			NetworkProperty network_property;
			std::vector<Capture> captures;
			std::vector<std::pair<double, double>> pressure_vs_time;
				
		};
    
		std::vector<Simulation> simulations;
		void write_to_file(const std::string& filename) const;
	};
}

#endif
