#include "simulate/menu.h"

void simulate::Menu::test_generate_and_plot()
{
	auto state = StepPreparation::generate_state();
	dst::States states;
	for(int i = 0; i < 2; ++ i)
	{
		state.id_step = i;
		states.push_back(state);
		Step1TubeFlowCoefficient::assign_resistance_and_capillary_pressure_to_tubes(state);
		states.push_back(state);
		Step2Pressure::generate_linear_equations_and_assign_pressure_to_node(state);
		states.push_back(state);
		Step3Velocity::calculate_and_assign_flow_rate_and_velocity_to_tube(state);
		states.push_back(state);
		Step4TimeStep::assign_time_step_to_state(state);
		states.push_back(state);
		Step5Displacement::assign_volume_length_displacement(state);
		states.push_back(state);
		Step6PourIntoNode::pour_from_tubes_to_node_tank(state);
		states.push_back(state);
		Step7InjectEvacuate::inject_and_evacuate_fluid_from_system(state);
		states.push_back(state);
		Step8Distribute::distribute_fluids_from_node_to_tube(state);
	}

	visualize::Menu visualize_menu; // the plots are dumped in this class
	visualize::Property visualize_property;
	visualize_menu.flow(states, visualize_property);
	io::FileWrite::flow(visualize_menu.out());

}

