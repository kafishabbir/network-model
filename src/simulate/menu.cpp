#include "simulate/menu.h"


void simulate::Menu::generate_and_plot()
{
	nst::State state = simulate::Step0Initialization::generate_state();

	simulate::StepPreparation::calculate_and_assign_resistance_and_capillary_pressures_to_tubes(state);
	simulate::Step1Pressure::solve_and_assign_pressure_at_nodes(state);
	simulate::Step2FlowRate::calculate_and_assign_flow_rates_to_tubes(state);
	simulate::Step3Velocity::calculate_and_assign_velocity_to_tubes(state);
	simulate::Step4TimeStep::assign_time_step_to_state(state);

	dst::States states{state};

	visualize::Menu visualize_menu; // the plots are dumped in this class
	visualize::Property visualize_property;
	visualize_menu.flow(states, visualize_property);
	io::FileWrite::flow(visualize_menu.out());
}
