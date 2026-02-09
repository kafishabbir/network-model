#include "simulate/menu.h"

void simulate::Menu::set_boundaries(nst::State& state)
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
	state.tubes[0].length = 4;
	state.tubes[5].radius = 0.85;


	//state.tubes[1].fluid_first = 1;
	//state.tubes[1].mpos = {0.8};

	//state.tubes[2].fluid_first = 1;
	//state.tubes[2].mpos = {0.2};

	state.tubes[5].fluid_first = 0;
	state.tubes[5].mpos = {0.2};

	//state.tubes[6].fluid_first = 1;
	//state.tubes[6].mpos = {0.3, 0.5, 0.7};

}

void simulate::Menu::generate_and_plot()
{
	visualize::Menu visualize_menu; // the plots are dumped in this class
	visualize::Property visualize_property;

	nst::State state = ic::DisplacementTest::generate_rectangular();
	set_boundaries(state);

	simulate::StepPreparation::calculate_and_assign_resistance_and_capillary_pressures_to_tubes(state);
	simulate::Step1Pressure::solve_and_assign_pressure_at_nodes(state);
	simulate::Step2FlowRate::calculate_and_assign_flow_rates_to_tubes(state);
	simulate::Step3Velocity::calculate_and_assign_velocity_to_tubes(state);
	simulate::Step4TimeStep::assign_time_step_to_state(state);

	dst::States states{state};
	visualize_menu.flow(states, visualize_property);
	io::FileWrite::flow(visualize_menu.out());
}
