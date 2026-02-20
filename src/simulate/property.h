#ifndef SIMULATE_PROPERTY_H
#define SIMULATE_PROPERTY_H

#include "utility/str.h"

namespace simulate
{
    class Property
    {
        public:

        enum class TypeSimulation
        {
			test_simple,
			test_random,
			periodic_const_pressure_variable_porosity,
			periodic_const_volume_injection_variable_porosity,
			periodic_const_pressure_const_porosity,
			periodic_const_volume_injection_const_porosity
		};
		// choose the type of simulation
		TypeSimulation type_simulation;

		int n_tube_rows;
		int n_tube_cols;
		int id_fluid_inject;

		double constant_sigma;
		double constant_radius_contrast;
		double constant_mu1_by_mu2;
		double constant_mu_scale;
		double constant_length_scale;

		double capture_frequency_in_volume_fraction;
		double volume_max_to_inject;

		int n_periods;
		double inlet_pressure;

		Property();

		std::string str() const;
    };
}

#endif
