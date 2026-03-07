#include "step/part10-measure.h"
#include "simulate/assign.h"
#include "simulate/measure.h"














compulsory(dst::System& system)
{
	calculated.fluid_in_system = simulate::Measure::fluid_in_system;
	calculated.saturation = ;
	calculated.average_pressure;
}

std::vector<std::pair<double, double>> step::Part10Measure::generate_saturation_vs_x(
	const dst::System& system
)
{
	std::vector<nst::Tank> tanks(system.parameter.geometry.n_tube_cols);
	
	const int n_tanks = tanks.size();
	
	for(const auto& tube: system.state.tubes)
	{
		const double x1 = system.state.nodes[tube.id_node_first].x;
		const double x2 = system.state.nodes[tube.id_node_second].x;
		const double x = (x1 + x2) / 2;
		
		const int index = std::floor(x * n_tanks);
		tanks.at(index).add_fluid(simulate::Measure::tube_inventory(tube));
	}
	
	std::vector<std::pair<double, double>> v;
	
	for(int i = 0; i < n_tanks; ++ i)
	{
		const double x = (0.5 + i) / n_tanks;
		v.push_back({x, tanks[i].saturation()});
	}
	
	return v;
}


std::vector<std::pair<double, double>> step::Part10Measure::generate_pressure_vs_y(
	const dst::System& system
)
{
	std::vector<std::pair<double, double>> v;
	
	for(const auto& node: system.state.nodes)
	{
		if(node.is_open_boundary && node.is_inlet)
		{
			v.push_back({node.y, node.calculated.pressure});
		}
	}
	
	std::sort(v.begin(), v.end());
	
	return v;
}


double step::Part10Measure::total_delta(
	const dst::System& system
)
{
	const double vol = system.state.measured.initial_total_fluid.volume_total();
	const double volume_total_injected = system.state.measured.total_fluid_added.volume_total();
	const double volume_total_evacuated = system.state.measured.total_fluid_evacuated.volume_total();

	return std::abs(volume_total_injected - volume_total_evacuated) / vol;
}

double step::Part10Measure::water_delta(
	const dst::System& system
)
{
	const double vol = system.state.measured.initial_total_fluid.volume_total();

	const double water_initial = system.state.measured.initial_total_fluid.volume_water();
	const double water_current = system.state.calculated.fluid_in_system.volume_water();
	const double water_injected = system.state.measured.total_fluid_added.volume_water();
	const double water_evacuated = system.state.measured.total_fluid_evacuated.volume_water();

	return std::abs((water_injected + water_initial) - (water_evacuated + water_current)) / vol;
}

double step::Part10Measure::oil_delta(
	const dst::System& system
)
{
	const double vol = system.state.measured.initial_total_fluid.volume_total();

	const double oil_initial = system.state.measured.initial_total_fluid.volume_oil();
	const double oil_current = system.state.calculated.fluid_in_system.volume_oil();
	const double oil_injected = system.state.measured.total_fluid_added.volume_oil();
	const double oil_evacuated = system.state.measured.total_fluid_evacuated.volume_oil();

	return std::abs((oil_injected + oil_initial) - (oil_evacuated + oil_current)) / vol;
}


capture(dst::System& system)
{
	calculated.pressure_vs_y = generate_pressure_vs_y(system);
	calculated.saturation_vs_x = generate_saturation_vs_x(system);
	
	
	system.state.calculated.volume_total_delta = total_delta(system);
	system.state.calculated.water_volume_delta = water_delta(system);
	system.state.calculated.oil_volume_delta = oil_delta(system);
	
}

/*
 * 
 * 
 high_frequency_measure(dst::System& system)
{
	struct HighFrequencyData
{
	double time;
	double pressure;
	double saturation;
	double flow_rate;
};
std::vector<HighFrequencyData> high_frequency_data_v;
 * 
 * 
 * 
 */

























double step::Part10Measure::find_average_pressure(
	const dst::System& system
)
{
	double sum = 0;
	for(const auto& node: system.state.nodes)
	{
		if(node.is_open_boundary && node.is_inlet)
		{
			sum += node.calculated.pressure;
		}
	}
	
	return sum / system.parameter.geometry.n_inject_boundaries;
}

void step::Part10Measure::measure(
	dst::System& system
)
{
	simulate::Assign::assign_type_fluid_contact(system);
	system.state.calculated.fluid_in_system = simulate::Measure::fluid_in_system(system);
	system.state.calculated.saturation = system.state.calculated.fluid_in_system.volume_water() / system.state.calculated.fluid_in_system.volume_total();

	
	if(system.state.reference.id_step % 20 == 0)
	{
		system.state.calculated.average_pressure = find_average_pressure(system);
		
		dst::State::HighFrequencyData high_frequency_data;
		high_frequency_data.time = system.state.measured.time_elapsed;
		high_frequency_data.pressure = system.state.calculated.average_pressure;
		high_frequency_data.saturation = system.state.calculated.saturation;
		high_frequency_data.flow_rate = system.state.calculated.fluid_added.volume_total() / system.state.calculated.time_step;
		
		system.state.high_frequency_data_v.push_back(high_frequency_data);
	}
}





void step::Part10Measure::assign_saturation_and_pressure_vs_coordinate(
	dst::System& system
)
{
	
}



