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
