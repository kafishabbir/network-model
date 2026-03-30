#include "step/part10-measure.h"
#include "simulate/assign.h"
#include "simulate/measure.h"
#include "simulate/accuracy.h"

void step::Part10Measure::compulsory(dst::System& system)
{
	system.state.calculated.fluid_in_system = simulate::Measure::fluid_in_system(system);
	system.state.calculated.saturation = system.state.calculated.fluid_in_system.volume_water() / system.state.calculated.fluid_in_system.volume_total();
	system.state.calculated.average_pressure = simulate::Measure::find_average_pressure(system);
}

void step::Part10Measure::capture(dst::System& system)
{
	simulate::Assign::assign_type_fluid_contact(system);
	system.state.calculated.pressure_vs_y = simulate::Measure::generate_pressure_vs_y(system);
	system.state.calculated.saturation_vs_x = simulate::Measure::generate_saturation_vs_x(system);
	system.state.calculated.squared_data_v = simulate::Measure::generate_squared_data(system);
	
	system.state.calculated.volume_total_delta = simulate::Accuracy::total_delta(system);
	system.state.calculated.water_volume_delta = simulate::Accuracy::water_delta(system);
	system.state.calculated.oil_volume_delta = simulate::Accuracy::oil_delta(system);
}

void step::Part10Measure::high_frequency_data(dst::System& system)
{
	dst::Measured::HighFrequencyData hf_data;
	hf_data.time = system.state.measured.time_elapsed;
	hf_data.pressure = system.state.calculated.average_pressure;
	hf_data.saturation = system.state.calculated.saturation;
	hf_data.flow_rate = system.state.calculated.fluid_added.volume_total() / system.state.calculated.time_step;
	
	system.measured.high_frequency_data_v.push_back(hf_data);
}
