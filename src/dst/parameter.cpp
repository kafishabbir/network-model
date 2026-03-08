#include "dst/parameter.h"
#include <sstream>
#include <iomanip>


std::string dst::Parameter::str_cmd() const
{
	std::stringstream ss;
	
	// Set precision for floating point values
	ss << std::setprecision(3);
	
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
	
	ss << "\n";
	ss << "PHYSICAL CONSTANTS:\n";
	ss << "-------------------\n";
	ss << "sigma = " << constant_physical.sigma << "\n";
	ss << "viscosity_water = " << constant_physical.viscosity_water << "\n";
	ss << "viscosity_oil = " << constant_physical.viscosity_oil << "\n";
	
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


std::string dst::Parameter::str() const
{
    std::stringstream ss;
    
    ss << "\\begin{enumerate}\n";
    
    // SIMULATION PARAMETERS
    ss << "\\item " << "SIMULATION PARAMETERS:" << "\n";
    ss << "\\begin{enumerate}\n";
    ss << "\\item is\\_flow\\_as\\_opposed\\_to\\_test = " << (simulation.is_flow_as_opposed_to_test ? "true" : "false") << "\n";
    ss << "\\item is\\_flow\\_const\\_flow\\_rate = " << (simulation.is_flow_const_flow_rate ? "true" : "false") << "\n";
    ss << "\\item is\\_const\\_porosity = " << (simulation.is_const_porosity ? "true" : "false") << "\n";
    ss << "\\item id\\_fluid\\_inject = " << simulation.id_fluid_inject << "\n";
    ss << "\\item inlet\\_pressure = $" << s(simulation.inlet_pressure) << "$\n";
    ss << "\\end{enumerate}\n";
    
    // GEOMETRY
    ss << "\\item " << "GEOMETRY:" << "\n";
    ss << "\\begin{enumerate}\n";
    ss << "\\item $n_{\\text{tube rows}} = " << geometry.n_tube_rows << "$\n";
    ss << "\\item $n_{\\text{tube cols}} = " << geometry.n_tube_cols << "$\n";
    ss << "\\item $\\text{radius contrast} = " << s(geometry.radius_contrast) << "$\n";
    ss << "\\item $\\text{length scale} = " << s(geometry.length_scale) << "$\n";
    ss << "\\item $n_{\\text{periods}} = " << s(geometry.n_periods) << "$\n";
    ss << "\\item $n_{\\text{inject boundaries}} = " << geometry.n_inject_boundaries << "$\n";
    ss << "\\end{enumerate}\n";
    
    // GEOMETRY DISTRIBUTIONS
    ss << "\\item " << "GEOMETRY DISTRIBUTIONS:" << "\n";
    ss << "\\begin{enumerate}\n";
    
    ss << "\\item RADIUS DISTRIBUTION:\n";
    ss << "\\begin{enumerate}\n";
    ss << "\\item ratio = $" << s(geometry_distributions.radius.ratio) << "$\n";
    ss << "\\item $r_{\\text{av}} = " << s(geometry_distributions.radius.average) << "$\n";
    ss << "\\item $r_{\\min} = " << s(geometry_distributions.radius.min) << "$\n";
    ss << "\\item $r_{\\max} = " << s(geometry_distributions.radius.max) << "$\n";
    ss << "\\item $\\sigma_r^2 = " << s(geometry_distributions.radius.variance) << "$\n";
    ss << "\\end{enumerate}\n";
    
    ss << "\\item LENGTH DISTRIBUTION:\n";
    ss << "\\begin{enumerate}\n";
    ss << "\\item ratio = $" << s(geometry_distributions.length.ratio) << "$\n";
    ss << "\\item $l_{\\text{av}} = " << s(geometry_distributions.length.average) << "$\n";
    ss << "\\item $l_{\\min} = " << s(geometry_distributions.length.min) << "$\n";
    ss << "\\item $l_{\\max} = " << s(geometry_distributions.length.max) << "$\n";
    ss << "\\item $\\sigma_l^2 = " << s(geometry_distributions.length.variance) << "$\n";
    ss << "\\end{enumerate}\n";
    
    ss << "\\item VOLUME DISTRIBUTION:\n";
    ss << "\\begin{enumerate}\n";
    ss << "\\item ratio = $" << s(geometry_distributions.volume.ratio) << "$\n";
    ss << "\\item $V_{\\text{av}} = " << s(geometry_distributions.volume.average) << "$\n";
    ss << "\\item $V_{\\min} = " << s(geometry_distributions.volume.min) << "$\n";
    ss << "\\item $V_{\\max} = " << s(geometry_distributions.volume.max) << "$\n";
    ss << "\\item $\\sigma_V^2 = " << s(geometry_distributions.volume.variance) << "$\n";
    ss << "\\end{enumerate}\n";
    
    ss << "\\end{enumerate}\n";
    
    // PHYSICAL CONSTANTS
    ss << "\\item " << "PHYSICAL CONSTANTS:" << "\n";
    ss << "\\begin{enumerate}\n";
    ss << "\\item $\\sigma = " << s(constant_physical.sigma) << "$\n";
    ss << "\\item $\\mu_w = " << s(constant_physical.viscosity_water) << "$\n";
    ss << "\\item $\\mu_o = " << s(constant_physical.viscosity_oil) << "$\n";
    ss << "\\end{enumerate}\n";
    
    // COMPUTATIONAL CONSTANTS
    ss << "\\item " << "COMPUTATIONAL CONSTANTS:" << "\n";
    ss << "\\begin{enumerate}\n";
    ss << "\\item $\\Delta t_{\\text{resolution}} = " << s(constant_computational.time_step_resolution) << "$\n";
    ss << "\\end{enumerate}\n";
    
    // PLOT PARAMETERS
    ss << "\\item " << "PLOT PARAMETERS:" << "\n";
    ss << "\\begin{enumerate}\n";
    ss << "\\item $V_{\\max\\ \\text{to inject}} = " << s(plot.volume_max_to_inject) << "$\n";
    ss << "\\item $f_{\\text{capture}} = " << s(plot.capture_frequency_in_volume_fraction) << "$\n";
    ss << "\\end{enumerate}\n";
    
    ss << "\\end{enumerate}\n";
    
    return ss.str();
}
