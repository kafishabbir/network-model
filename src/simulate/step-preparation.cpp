#include "simulate/step-preparation.h"

void simulate::StepPreparation::assign_resistance_to_tubes(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.resistance_coefficient =
			simulate::Physics::calculate_resistance(tube, state);
	}
}

void simulate::StepPreparation::assign_capillary_pressure_magnitude_to_tubes(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.capillary_pressure_magnitude =
			simulate::Physics::calculate_capillary_pressure_magnitude(tube, state);
	}
}

void simulate::StepPreparation::assign_connections_id_tube_to_nodes(nst::State& state)
{
	const int n_tubes = state.tubes.size();
	auto& nodes = state.nodes;
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = state.tubes[i];
		const int id_node_first = tube.id_node_first;
		const int id_node_second = tube.id_node_second;

		nodes[id_node_first].calculated.connections_id_tube_v.push_back(i);
		nodes[id_node_second].calculated.connections_id_tube_v.push_back(i);
	}
}


