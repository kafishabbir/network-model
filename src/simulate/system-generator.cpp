#include "simulate/system-generator.h"

#include "ic/geometry-rand.h"
#include "ic/geometry-flow.h"

std::pair<nst::Nodes, nst::Tubes>
simulate::SystemGenerator::choose_network_geometry(
	const dst::Parameter& parameter
)
{
	if(parameter.simulation.is_flow_as_opposed_to_test)
	{
		if(parameter.simulation.is_const_porosity)
		{
			if(parameter.geometry.is_random_radius)
			{
				return ic::GeometryFlow::network_geometry_const_porosity_random_radius(
					parameter.geometry.n_tube_rows,
					parameter.geometry.n_tube_cols,
					parameter.simulation.id_fluid_inject,
					parameter.geometry.radius_contrast,
					parameter.geometry.length_scale	
				);
			}
			return ic::GeometryFlow::network_geometry_const_porosity(
				parameter.geometry.n_tube_rows,
				parameter.geometry.n_tube_cols,
				parameter.simulation.id_fluid_inject,
				parameter.geometry.radius_contrast,
				parameter.geometry.length_scale,
				parameter.geometry.n_periods,
				parameter.geometry.is_skewed
			);
		}
		else // is const length 
		{
			if(parameter.geometry.is_random_radius)
			{
				return ic::GeometryFlow::network_geometry_random_radius(
					parameter.geometry.n_tube_rows,
					parameter.geometry.n_tube_cols,
					parameter.simulation.id_fluid_inject,
					parameter.geometry.radius_contrast,
					parameter.geometry.length_scale
				);
			}
			return ic::GeometryFlow::network_geometry(
				parameter.geometry.n_tube_rows,
				parameter.geometry.n_tube_cols,
				parameter.simulation.id_fluid_inject,
				parameter.geometry.radius_contrast,
				parameter.geometry.length_scale,
				parameter.geometry.n_periods,
				parameter.geometry.is_skewed
			);
		}
	}
	
	// For very extreme testing -- just uncomment this
	// return ic::GeometryRand::network_geometry();
	
	return ic::GeometryBase::rectangular(
		parameter.geometry.n_tube_rows,
		parameter.geometry.n_tube_cols,
		parameter.simulation.id_fluid_inject
	);
	
}

int simulate::SystemGenerator::count_inlet_nodes(
	const dst::State& state
)
{
	int count = 0;
	for(const auto& node: state.nodes)
	{
		if(node.is_open_boundary && node.is_inlet)
		{
			++ count;
		}
	}
	
	return count;	
}
dst::Parameter::GeometryDistributions::Distribution
simulate::SystemGenerator::find_distribution_radius(
	const dst::State& state
)
{
	dst::Parameter::GeometryDistributions::Distribution dist;
	
	double sum = 0.0;
	double min_val = state.tubes.front().radius;
	double max_val = state.tubes.front().radius;
	
	for (const auto& tube : state.tubes)
	{
		double radius = tube.radius;
		sum += radius;
		min_val = std::min(min_val, radius);
		max_val = std::max(max_val, radius);
	}
	
	dist.average = sum / state.tubes.size();
	dist.min = min_val;
	dist.max = max_val;
	dist.ratio = max_val / min_val;
	
	// Calculate variance first (for standard deviation)
	double variance_sum = 0.0;
	for (const auto& tube : state.tubes)
	{
		double diff = tube.radius - dist.average;
		variance_sum += diff * diff;
	}
	double variance = variance_sum / state.tubes.size();
	
	// Calculate coefficient of variation (sqrt(variance) / average) and store in dist.variance
	double std_dev = std::sqrt(variance);
	if (dist.average != 0.0) {
		dist.variance = std_dev / dist.average;  // Now storing coefficient of variation
	} else {
		dist.variance = 0.0;
	}
	
	return dist;
}

dst::Parameter::GeometryDistributions::Distribution
simulate::SystemGenerator::find_distribution_length(
	const dst::State& state
)
{
	dst::Parameter::GeometryDistributions::Distribution dist;
	
	double sum = 0.0;
	double min_val = state.tubes.front().length;
	double max_val = state.tubes.front().length;
	
	for (const auto& tube : state.tubes)
	{
		double length = tube.length;
		sum += length;
		min_val = std::min(min_val, length);
		max_val = std::max(max_val, length);
	}
	
	dist.average = sum / state.tubes.size();
	dist.min = min_val;
	dist.max = max_val;
	dist.ratio = max_val / min_val;
	
	// Calculate variance first (for standard deviation)
	double variance_sum = 0.0;
	for (const auto& tube : state.tubes)
	{
		double diff = tube.length - dist.average;
		variance_sum += diff * diff;
	}
	double variance = variance_sum / state.tubes.size();
	
	// Calculate coefficient of variation (sqrt(variance) / average) and store in dist.variance
	double std_dev = std::sqrt(variance);
	if (dist.average != 0.0) {
		dist.variance = std_dev / dist.average;  // Now storing coefficient of variation
	} else {
		dist.variance = 0.0;
	}
	
	return dist;
}

dst::Parameter::GeometryDistributions::Distribution
simulate::SystemGenerator::find_distribution_volume(
	const dst::State& state
)
{
	dst::Parameter::GeometryDistributions::Distribution dist;
	
	double sum = 0.0;
	double min_val = state.tubes.front().volume();
	double max_val = state.tubes.front().volume();
	
	for (const auto& tube : state.tubes)
	{
		double volume = tube.volume();
		sum += volume;
		min_val = std::min(min_val, volume);
		max_val = std::max(max_val, volume);
	}
	
	dist.average = sum / state.tubes.size();
	dist.min = min_val;
	dist.max = max_val;
	dist.ratio = max_val / min_val;
	
	// Calculate variance first (for standard deviation)
	double variance_sum = 0.0;
	for (const auto& tube : state.tubes)
	{
		double diff = tube.volume() - dist.average;
		variance_sum += diff * diff;
	}
	double variance = variance_sum / state.tubes.size();
	
	// Calculate coefficient of variation (sqrt(variance) / average) and store in dist.variance
	double std_dev = std::sqrt(variance);
	if (dist.average != 0.0) {
		dist.variance = std_dev / dist.average;  // Now storing coefficient of variation
	} else {
		dist.variance = 0.0;
	}
	
	return dist;
}


dst::Parameter simulate::SystemGenerator::parameter_processed(
	dst::Parameter parameter,
	const dst::State& state
)
{
	parameter.geometry.n_inject_boundaries = count_inlet_nodes(state);
	parameter.geometry_distributions.radius = find_distribution_radius(state);
	parameter.geometry_distributions.length = find_distribution_length(state);
	parameter.geometry_distributions.volume = find_distribution_volume(state);
	
	return parameter;
}

std::pair<dst::Parameter, dst::State>
simulate::SystemGenerator::generate_parameter_processed_and_basic_state(
	const dst::Parameter& parameter
)
{
	dst::State state(choose_network_geometry(parameter));
	return {parameter_processed(parameter, state), state};
}
