#include "simulate/menu.h"

dst::States simulate::Menu::run(const simulate::Property& simulate_property)
{
	utility::Time time;

	auto state = Step0Preparation::generate_state(simulate_property);
	auto states = steps(state);

	std::cout << "Program ran for: " << time.passed() << " ms" << std::endl;
    std::cout << "Fraction of time=" << std::setprecision(2)
		<< state.measured.time_taken_by_solving_linear_equations / time.passed();
    std::cout <<  ", spent on linear equations." << std::endl;

	return states;
}


dst::States simulate::Menu::steps(dst::State& state)
{
	dst::States states;

	bool is_solver_prepared = false;
	Eigen::SimplicialLLT<Eigen::SparseMatrix<double>> solver;

	for(int i = 0; decide_if_more_fluid_still_needs_to_be_injected(state); ++ i)
	{
		state.reference.id_step = i;

		perform_single_time_step(state, solver);

		if(decide_if_capture_state_for_plot(state))
		{
			states.push_back(state);
		}
	}

	return states;
}


void simulate::Menu::perform_single_time_step(
	dst::State& state,
	bool& is_solver_prepared,
	Eigen::SimplicialLLT<Eigen::SparseMatrix<double>>& solver
)
{
	auto& comment = state.reference.comment;

	//int j = 0;
	Utility::reset_calculated(state);
		//comment = "reset-calculated";
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
		//comment = "measure";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;
}
