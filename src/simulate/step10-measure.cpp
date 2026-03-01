#include "simulate/step10-measure.h"


double simulate::Step10Measure::total_delta(const nst::State& state)
{
	const double vol = state.measured.initial_total_fluid.volume_total();
	const double volume_total_injected = state.measured.total_fluid_added.volume_total();
	const double volume_total_evacuated = state.measured.total_fluid_evacuated.volume_total();

	return std::abs(volume_total_injected - volume_total_evacuated) / vol;
}

double simulate::Step10Measure::water_delta(const nst::State& state)
{
	const double vol = state.measured.initial_total_fluid.volume_total();

	const double water_initial = state.measured.initial_total_fluid.volume_water();
	const double water_current = state.calculated.total_fluid_in_system.volume_water();
	const double water_injected = state.measured.total_fluid_added.volume_water();
	const double water_evacuated = state.measured.total_fluid_evacuated.volume_water();

	return std::abs((water_injected + water_initial) - (water_evacuated + water_current)) / vol;
}

double simulate::Step10Measure::oil_delta(const nst::State& state)
{
	const double vol = state.measured.initial_total_fluid.volume_total();

	const double oil_initial = state.measured.initial_total_fluid.volume_oil();
	const double oil_current = state.calculated.total_fluid_in_system.volume_oil();
	const double oil_injected = state.measured.total_fluid_added.volume_oil();
	const double oil_evacuated = state.measured.total_fluid_evacuated.volume_oil();

	return std::abs((oil_injected + oil_initial) - (oil_evacuated + oil_current)) / vol;
}

double simulate::Step10Measure::find_average_pressure(const nst::State& state)
{
	double sum = 0;
	for(const auto& node: state.nodes)
	{
		if(node.is_open_boundary && node.is_inlet)
		{
			sum += node.calculated.pressure;
		}
	}
	
	return sum / state.reference.n_inject_boundaries;
}

void simulate::Step10Measure::measure(nst::State& state)
{
	Utility::assign_type_fluid_contact(state);
	state.calculated.total_fluid_in_system = simulate::Utility::total_fluid_in_system(state);
	state.calculated.saturation = state.calculated.total_fluid_in_system.volume_water() / state.calculated.total_fluid_in_system.volume_total();
	state.calculated.volume_total_delta = total_delta(state);
	state.calculated.water_volume_delta = water_delta(state);
	state.calculated.oil_volume_delta = oil_delta(state);
	
	if(state.reference.id_step % 20 == 0)
	{
		state.calculated.average_pressure = find_average_pressure(state);
		
		nst::State::HighFrequencyData high_frequency_data;
		high_frequency_data.time = state.measured.time_elapsed;
		high_frequency_data.pressure = state.calculated.average_pressure;
		high_frequency_data.saturation = state.calculated.saturation;
		high_frequency_data.flow_rate = state.calculated.fluid_added.volume_total() / state.calculated.time_step;
		
		state.high_frequency_data_v.push_back(high_frequency_data);
	}
}

std::vector<std::pair<double, double>> simulate::Step10Measure::generate_saturation_vs_x(
	const nst::State& state
)
{
	std::vector<nst::Tank> tanks(state.reference.n_tube_cols);
	
	const double unity_to_integer_factor = tanks.size();
	
	for(const auto& tube: state.tubes)
	{
		const double x1 = state.nodes[tube.id_node_first].x;
		//const double y1 = nodes[tube.id_node_first].y;
		const double x2 = state.nodes[tube.id_node_second].x;
		//const double y2 = nodes[tube.id_node_second].y;
		const double x = (x1 + x2) / 2;
		
		const int index = std::floor(x * unity_to_integer_factor);
		tanks[index].add_fluid(Utility::tube_inventory(tube));
	}
	std::vector<std::pair<double, double>> v;
	const int n_tanks = tanks.size();
	for(int i = 0; i < n_tanks; ++ i)
	{
		const double x = (0.5 + i) / unity_to_integer_factor;
		v.push_back({x, tanks[i].saturation()});
	}
	
	return v;
}



std::vector<std::pair<double, double>> simulate::Step10Measure::generate_pressure_vs_y(
	const nst::State& state
)
{
	std::vector<nst::Tank> tanks(state.reference.n_tube_rows);
	
	//const double unity_to_integer_factor = tanks.size();
	std::vector<std::pair<double, double>> v;
	for(const auto& node: state.nodes)
	{
		if(node.is_open_boundary && node.is_inlet)
		{
			v.push_back({node.y, node.calculated.pressure});
		}
	}
	
	std::sort(v.begin(), v.end());
	
	return v;
}

void simulate::Step10Measure::assign_saturation_and_pressure_vs_coordinate(nst::State& state)
{
	state.calculated.saturation_vs_x = generate_saturation_vs_x(state);
	state.calculated.pressure_vs_y = generate_pressure_vs_y(state);
}

