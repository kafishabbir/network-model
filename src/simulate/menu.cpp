#include "simulate/menu.h"

void simulate::Menu::test_generate_and_plot()
{
	auto state = Step0Preparation::generate_state();
	dst::States states;
	auto& comment = state.calculated.comment;
	for(int i = 0; i < 28; ++ i)
	{
		comment = "preparation";
		state.calculated.id_step = i;
		states.push_back(state);

		Step1TubeFlowCoefficient::assign_resistance_and_capillary_pressure_to_tubes(state);
		comment = "assign-resistance-and-capillary-pressure-to-tubes";
		//states.push_back(state);

		Step2Pressure::generate_linear_equations_and_assign_pressure_to_node(state);
		comment = "generate-linear-equations-and-assign-pressure-to-node";
		states.push_back(state);

		Step3Velocity::calculate_and_assign_flow_rate_and_velocity_to_tube(state);
		comment = "calculate-and-assign-flow-rate-and-velocity-to-tube";
		states.push_back(state);

		Step4TimeStep::assign_time_step_to_state(state);
		comment = "assign-time-step-to-state";
		states.push_back(state);

		Step5Displacement::assign_volume_length_displacement(state);
		comment = "assign-volume-length-displacement";
		states.push_back(state);

		Step6PourIntoNode::pour_from_tubes_to_node_tank(state);
		comment = "pour-from-tubes-to-node-tank";
		//states.push_back(state);

		Step7InjectEvacuate::inject_and_evacuate_fluid_from_system(state);
		comment = "inject-and-evacuate-fluid-from-system";
		states.push_back(state);

		Step8Distribute::distribute_fluids_from_node_to_tube(state);
		comment = "distribute-fluids-from-node-to-tube";
		states.push_back(state);

		Step9UpdateTubeMpos::update_tube_mpos_according_to_proportion(state);
		comment = "update-tube-mpos-according-to-proportion";
		states.push_back(state);
	}

	visualize::Menu visualize_menu; // the plots are dumped in this class
	visualize::Property visualize_property;
	visualize_menu.flow(states, visualize_property);
	io::FileWrite::flow(visualize_menu.out());

}

