#include "simulate/menu.h"

void set_boundaries(nst::State& state)
{
	auto& nodes = state.nodes;
	nodes[0].is_open_boundary = true;
	nodes[5].is_open_boundary = true;
	nodes[2].is_open_boundary = true;
	nodes[7].is_open_boundary = true;

	nodes[0].pressure = 10;
	nodes[5].pressure = 10;
	nodes[2].pressure = 1;
	nodes[7].pressure = 1;

	state.tubes[3].radius = 1.25;
	state.tubes[5].radius = 0.85;
}

void simulate::Menu::generate_and_plot()
{
	nst::State state = ic::DisplacementTest::generate_rectangular();
	visualize::Menu visualize_menu;
	set_boundaries(state);
	simulate::Step1Pressure::solve_and_assign_pressure_at_nodes(state);
	simulate::Step2FlowRate::calculate_and_assign_flow_rates_to_tubes(state);

	visualize_menu.flow({state});
	io::FileWrite::flow(visualize_menu.out());
}
