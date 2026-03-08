#include "step/part01-reference.h"
#include "simulate/assign.h"

void step::Part01Reference::reset_calculated(
	dst::System& system
)
{
	system.state.calculated = dst::State::Calculated();
	
	for(auto& node: system.state.nodes)
	{
		node.calculated = nst::Node::Calculated();
	}
	
	for(auto& tube: system.state.tubes)
	{
		tube.calculated = nst::Tube::Calculated();
	}
}

double step::Part01Reference::evaluate_mu(
	const nst::Tube& tube,
	const dst::System& system
)
{
	const double mu_water = system.parameter.constant_physical.viscosity_water;
	const double mu_oil = system.parameter.constant_physical.viscosity_oil;
	std::vector<double> mu_v{mu_water, mu_oil};
	
	const auto& mpos_long = tube.mpos_long();
	const int n = mpos_long.size();
	double sum = 0;
	
	for(int i = 1; i < n; ++ i)
	{
		sum += (mpos_long[i] - mpos_long[i - 1]) * mu_v[(i + 1) % 2];
	}
	
	return sum;
}

double step::Part01Reference::resistance_coefficient(
	const nst::Tube& tube,
	const dst::System& system
)
{
	const double r = tube.radius;
	const double l = tube.length;
	const double mu = evaluate_mu(tube, system);
	
	return std::acos(-1) / 8 * std::pow(r, 4) / mu / l;
}

void step::Part01Reference::resistance_coefficient(
	dst::System& system
)
{
	for(auto& tube: system.state.tubes)
	{
		tube.calculated.resistance_coefficient =
			resistance_coefficient(tube, system);
	}
}


std::pair<int, int> step::Part01Reference::add_pseudo_meniscus(
    const nst::Tube& tube, 
    const dst::System& system
)
{
	
    int n_meniscus = tube.mpos.size();
    int id_fluid_first = tube.id_fluid_first;
    int id_fluid_last = (id_fluid_first + n_meniscus) % 2;
    //return {id_fluid_first, n_meniscus};
    const auto& node_begin = system.state.nodes[tube.id_node_first];
    const auto& node_end = system.state.nodes[tube.id_node_second];
    
    if(node_begin.calculated.has_contact_with_water && (id_fluid_first == 1))
    {
        ++ n_meniscus;
        id_fluid_first = 0;
    }
    
    if(node_end.calculated.has_contact_with_water && (id_fluid_last == 1))
    {
        ++ n_meniscus;
    }
    
    return {id_fluid_first, n_meniscus};
}

double step::Part01Reference::capillary_pressure_magnitude(
	const nst::Tube& tube,
	const dst::System& system
)
{
	const auto& [id_fluid_first, n_meniscus] = add_pseudo_meniscus(tube, system);
	
	const double sigma = system.parameter.constant_physical.sigma;
	const double value_single_meniscus = 2.0 * sigma / tube.radius;
	
	const double sign_id_fluid_first = ((id_fluid_first == 0) ? 1 : -1);
	const double sign_n_meniscus = (n_meniscus % 2);
	

	return sign_id_fluid_first * sign_n_meniscus * value_single_meniscus;
}

void step::Part01Reference::capillary_pressure_magnitude(
	dst::System& system
)
{
	for(auto& tube: system.state.tubes)
	{
		tube.calculated.capillary_pressure_magnitude =
			capillary_pressure_magnitude(tube, system);
	}
}

void step::Part01Reference::run(
	dst::System& system
)
{
	reset_calculated(system);
	resistance_coefficient(system);
	capillary_pressure_magnitude(system);
	simulate::Assign::assign_type_fluid_contact(system);
}
