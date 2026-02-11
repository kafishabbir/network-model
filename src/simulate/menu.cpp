#include "simulate/menu.h"


void simulate::Menu::generate_and_plot()
{
	nst::State state = simulate::Step0Initialization::generate_state();

	simulate::StepPreparation::assign_connections_id_tube_to_nodes(state);
	dst::States states;
	for(int i = 0; i < 10; ++ i)
	{
		simulate::Step1Pressure::solve_and_assign_pressure_at_nodes(state);
		simulate::Step2FlowRate::calculate_and_assign_flow_rates_to_tubes(state);
		simulate::Step3Velocity::calculate_and_assign_velocity_to_tubes(state);
		simulate::Step4TimeStep::assign_time_step_to_state(state);
		states.push_back(state);
	}

	visualize::Menu visualize_menu; // the plots are dumped in this class
	visualize::Property visualize_property;
	visualize_menu.flow(states, visualize_property);
	io::FileWrite::flow(visualize_menu.out());
}
