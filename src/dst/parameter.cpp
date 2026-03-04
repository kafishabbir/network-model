#include "dst/parameter.h"
#include <sstream>
#include <iomanip>


std::string dst::Parameter::str_cmd() const
{
	std::stringstream ss;
	
	// Set precision for floating point values
	ss << std::fixed << std::setprecision(3);
	
	ss << "SIMULATION PARAMETERS:\n";
	ss << "----------------------\n";
	ss << "is_flow_as_opposed_to_test = " << (simulation.is_flow_as_opposed_to_test ? "true" : "false") << "\n";
	ss << "is_flow_const_flow_rate = " << (simulation.is_flow_const_flow_rate ? "true" : "false") << "\n";
	ss << "is_const_porosity = " << (simulation.is_const_porosity ? "true" : "false") << "\n";
	ss << "id_fluid_inject = " << simulation.id_fluid_inject << "\n";
	ss << "inlet_pressure = " << simulation.inlet_pressure << "\n";
	
	ss << "\n";
	ss << "GEOMETRY:\n";
	ss << "---------\n";
	ss << "n_tube_rows = " << geometry.n_tube_rows << "\n";
	ss << "n_tube_cols = " << geometry.n_tube_cols << "\n";
	ss << "radius_contrast = " << geometry.radius_contrast << "\n";
	ss << "length_scale = " << geometry.length_scale << "\n";
	ss << "n_periods = " << geometry.n_periods << "\n";
	ss << "n_inject_boundaries = " << geometry.n_inject_boundaries << "\n";
	
	//~ ss << "\n";
	//~ ss << "GEOMETRY DISTRIBUTIONS:\n";
	//~ ss << "------------------------\n";
	
	//~ ss << "  RADIUS DISTRIBUTION:\n";
	//~ ss << "  radius.average = " << geometry_distributions.radius.average << "\n";
	//~ ss << "  radius.min = " << geometry_distributions.radius.min << "\n";
	//~ ss << "  radius.max = " << geometry_distributions.radius.max << "\n";
	//~ ss << "  radius.variance = " << geometry_distributions.radius.variance << "\n";
	
	//~ ss << "\n";
	//~ ss << "  LENGTH DISTRIBUTION:\n";
	//~ ss << "  length.average = " << geometry_distributions.length.average << "\n";
	//~ ss << "  length.min = " << geometry_distributions.length.min << "\n";
	//~ ss << "  length.max = " << geometry_distributions.length.max << "\n";
	//~ ss << "  length.variance = " << geometry_distributions.length.variance << "\n";
	
	//~ ss << "\n";
	//~ ss << "  VOLUME DISTRIBUTION:\n";
	//~ ss << "  volume.average = " << geometry_distributions.volume.average << "\n";
	//~ ss << "  volume.min = " << geometry_distributions.volume.min << "\n";
	//~ ss << "  volume.max = " << geometry_distributions.volume.max << "\n";
	//~ ss << "  volume.variance = " << geometry_distributions.volume.variance << "\n";
	
	//~ ss << "\n";
	//~ ss << "PHYSICAL CONSTANTS:\n";
	//~ ss << "-------------------\n";
	//~ ss << "sigma = " << constant_physical.sigma << "\n";
	//~ ss << "viscosity_water = " << constant_physical.viscosity_water << "\n";
	//~ ss << "viscosity_oil = " << constant_physical.viscosity_oil << "\n";
	
	//~ ss << "\n";
	//~ ss << "COMPUTATIONAL CONSTANTS:\n";
	//~ ss << "-------------------------\n";
	//~ ss << "time_step_resolution = " << constant_computational.time_step_resolution << "\n";
	
	ss << "\n";
	ss << "PLOT PARAMETERS:\n";
	ss << "----------------\n";
	ss << "volume_max_to_inject = " << plot.volume_max_to_inject << "\n";
	ss << "capture_frequency_in_volume_fraction = " << plot.capture_frequency_in_volume_fraction << "\n";
	
	return ss.str();
}
