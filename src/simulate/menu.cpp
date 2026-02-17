#include "simulate/menu.h"

void simulate::Menu::test_generate_and_plot()
{
	utility::Time time;

	auto state = Step0Preparation::generate_state();

	//~ for(int i = 0; i < state.nodes.size(); ++ i)
	//~ {
		//~ auto& node = state.nodes[i];
		//~ if(node.reference.connections_id_tube_v.size() == 1)
		//~ {
			//~ std::cout << "i=" << i << "  ";
		//~ }
	//~ }

	//~ return;
	state.measured.initial_total_fluid = Step10Measure::total_fluid_in_system(state);
	dst::States states;
	auto& comment = state.reference.comment;

	bool is_solver_prepared = false;
	Eigen::SimplicialLLT<Eigen::SparseMatrix<double>> solver;

	//int j = 0;
	for(int i = 0; i < 1000; ++ i)
	{
		comment = "preparation";
		state.reference.id_step = i;

		Step0Preparation::reset_calculated(state);
			//if(i % 10 == 0)
			//states.push_back(state);
			//std::cout << "here" << j++ << std::endl;

		Step1TubeFlowCoefficient::assign_resistance_and_capillary_pressure_to_tubes(state);
			//comment = "assign-resistance-and-capillary-pressure-to-tubes";
			//states.push_back(state);
			//std::cout << "here" << j++ << std::endl;
		Step2Pressure::generate_symmetric_linear_equations_and_assign_pressure_to_node(state, is_solver_prepared, solver);
			//comment = "generate-linear-equations-and-assign-pressure-to-node";
			//states.push_back(state);
			//std::cout << "here" << j++ << std::endl;

		Step3Velocity::calculate_and_assign_flow_rate_and_velocity_to_tube(state);
			//comment = "calculate-and-assign-flow-rate-and-velocity-to-tube";
			//states.push_back(state);
			//std::cout << "here" << j++ << std::endl;

		Step4TimeStep::assign_time_step_to_state(state);
			//comment = "assign-time-step-to-state";
			//states.push_back(state);
			//std::cout << "here" << j++ << std::endl;

		Step5Displacement::assign_volume_length_displacement(state);
			//comment = "assign-volume-length-displacement";
			//states.push_back(state);
			//std::cout << "here" << j++ << std::endl;

		Step6PourIntoNode::pour_from_tubes_to_node_tank(state);
			//comment = "pour-from-tubes-to-node-tank";
			//states.push_back(state);
			//std::cout << "here" << j++ << std::endl;

		Step7InjectEvacuate::inject_and_evacuate_fluid_from_system(state);
			//comment = "inject-and-evacuate-fluid-from-system";
			//states.push_back(state);
			//std::cout << "here" << j++ << std::endl;

		Step8Distribute::distribute_fluids_from_node_to_tube(state);
			//comment = "distribute-fluids-from-node-to-tube";
			//states.push_back(state);
			//std::cout << "here" << j++ << std::endl;

		Step9UpdateTubeMpos::update_tube_mpos_according_to_proportion(state);
			//comment = "update-tube-mpos-according-to-proportion";
			//states.push_back(state);
			//std::cout << "here" << j++ << std::endl;

		Step10Measure::measure(state);

		comment = "all measurements done";
		//if(i % 200 == 0)
		//states.push_back(state);
	}

	visualize::Menu visualize_menu; // the plots are dumped in this class
	visualize::Property visualize_property;
	visualize_menu.flow(states, visualize_property);
	io::FileWrite::flow(visualize_menu.out());


    std::cout << "Program ran for: " << time.passed() << " ms" << std::endl;
    std::cout << "Fraction of time=" << std::setprecision(2);
    std::cout << state.measured.time_taken_by_solving_linear_equations / time.passed();
    std::cout <<  ", spent on linear equations." << std::endl;
}

