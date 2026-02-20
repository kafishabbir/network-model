#include "simulate/property.h"

simulate::Property::Property():
    type_simulation(TypeSimulation::test_simple),
    n_tube_rows(2),
    n_tube_cols(4),
    id_fluid_inject(0),
    constant_sigma(0.0),
    constant_radius_contrast(0.2),
    constant_mu1_by_mu2(1.0),
    constant_mu_scale(1.0),
    constant_length_scale(10),
    capture_frequency_in_volume_fraction(0.1),
    volume_max_to_inject(0.6),
    n_periods(0),
    inlet_pressure(0.0)
{}


std::string simulate::Property::str() const
{
    std::stringstream ss;

    ss << "type-simulation=";
    if (type_simulation == TypeSimulation::test_simple)
    {
        ss << "test-simple";
	}
    else if (type_simulation == TypeSimulation::test_random)
    {
        ss << "test-random";
	}
    else if (type_simulation == TypeSimulation::periodic_const_pressure_variable_porosity)
    {
        ss << "periodic-const-pressure-variable-porosity";
	}
    else if (type_simulation == TypeSimulation::periodic_const_volume_injection_variable_porosity)
    {
        ss << "periodic-const-volume-injection-variable-porosity";
	}
    else if (type_simulation == TypeSimulation::periodic_const_pressure_const_porosity)
    {
        ss << "periodic-const-pressure-const-porosity";
	}
    else if (type_simulation == TypeSimulation::periodic_const_volume_injection_const_porosity)
    {
        ss << "periodic-const-volume-injection-const-porosity";
	}
	ss << ", \n";
    ss << "n-tube-rows=" << n_tube_rows << ", \n";
    ss << "n-tube-cols=" << n_tube_cols << ", \n";
    ss << "id-fluid-inject=" << id_fluid_inject << ", \n";
    ss << "constant-sigma=" << utility::Str::d(constant_sigma) << ", \n";
    ss << "constant-radius-contrast=" << utility::Str::d(constant_radius_contrast) << ", \n";
    ss << "constant-mu1-by-mu2=" << utility::Str::d(constant_mu1_by_mu2) << ", \n";
    ss << "constant-mu-scale=" << utility::Str::d(constant_mu_scale) << ", \n";
    ss << "constant-length-scale=" << utility::Str::d(constant_length_scale) << ", \n";
    ss << "capture-frequency-in-volume-fraction=" << utility::Str::d(capture_frequency_in_volume_fraction) << ", \n";
    ss << "volume-max-to-inject=" << utility::Str::d(volume_max_to_inject) << ", \n";
    ss << "n-periods=" << n_periods << ", \n";
    ss << "inlet-pressure=" << utility::Str::d(inlet_pressure) << ".";

    return ss.str();
}
