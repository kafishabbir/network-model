#include "simulate/menu.h"
#include <cmath>
#include <iomanip>

dst::States simulate::Menu::run(const simulate::Property& simulate_property)
{
	utility::Time time;

	auto state = Step0Preparation::generate_state(simulate_property);

	std::cout << "Time to generate initial conditions = " <<  d(time.passed()) << " ms" << std::endl;

	std::cout << "\n\nSimulation started for: " << state.reference.comment << std::endl;
	auto states = steps(state);

	const auto time_program = time.passed();
	std::cout << "Program ran for: " << d(time_program) << " ms" << std::endl;
	std::cout << "Fraction of time="
		<< d(state.measured.time_taken_by_solving_linear_equations / time_program);
	std::cout <<  ", spent on linear equations." << std::endl;

	int count = 0;
	for(auto t_step: state.measured.time_taken_by_each_step)
	{
		std::cout << "step-" << count++ << " t=" << std::setw(5) << std::round(t_step) << "ms, tf=" << std::round(t_step / time_program * 100) << "%" << '\n';
	}
	return states;
}


dst::States simulate::Menu::steps(nst::State& state)
{
	dst::States states;

	bool is_solver_prepared = false;
	Eigen::SimplicialLLT<Eigen::SparseMatrix<double>> solver;

	for(int i = 0; Utility::decide_if_more_fluid_still_needs_to_be_injected(state); ++ i)
	{
		state.reference.id_step = i;

		perform_single_time_step(
			state,
			is_solver_prepared,
			solver
		);

		if(Utility::decide_if_capture_state_for_plot(state))
		{
			states.push_back(state);
			state.reference.comment = "";
		}
	}

	return states;
}


void simulate::Menu::perform_single_time_step(
	nst::State& state,
	bool& is_solver_prepared,
	Eigen::SimplicialLLT<Eigen::SparseMatrix<double>>& solver
)
{
	//auto& comment = state.reference.comment;

	//int j = 0;
		utility::Time time;
	Utility::reset_calculated(state);
		state.measured.time_taken_by_each_step[0] += time.passed();
		//comment = "reset-calculated";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

		time.reset();
	Step1TubeFlowCoefficient::assign_resistance_and_capillary_pressure_to_tubes(state);
		state.measured.time_taken_by_each_step[1] += time.passed();
		//comment = "assign-resistance-and-capillary-pressure-to-tubes";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

		time.reset();
	Step2Pressure::generate_symmetric_linear_equations_and_assign_pressure_to_node(state, is_solver_prepared, solver);
		state.measured.time_taken_by_each_step[2] += time.passed();
		//comment = "generate-linear-equations-and-assign-pressure-to-node";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

		time.reset();
	Step3Velocity::calculate_and_assign_flow_rate_and_velocity_to_tube(state);
		state.measured.time_taken_by_each_step[3] += time.passed();
		//comment = "calculate-and-assign-flow-rate-and-velocity-to-tube";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

		time.reset();
	Step4TimeStep::assign_time_step_to_state(state);
		state.measured.time_taken_by_each_step[4] += time.passed();
		//comment = "assign-time-step-to-state";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

		time.reset();
	Step5Displacement::assign_volume_length_displacement(state);
		state.measured.time_taken_by_each_step[5] += time.passed();
		//comment = "assign-volume-length-displacement";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

		time.reset();
	Step6PourIntoNode::pour_from_tubes_to_node_tank(state);
		state.measured.time_taken_by_each_step[6] += time.passed();
		//comment = "pour-from-tubes-to-node-tank";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

		time.reset();
	Step7InjectEvacuate::inject_and_evacuate_fluid_from_system(state);
		state.measured.time_taken_by_each_step[7] += time.passed();
		//comment = "inject-and-evacuate-fluid-from-system";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

		time.reset();
	Step8Distribute::distribute_fluids_from_node_to_tube(state);
		state.measured.time_taken_by_each_step[8] += time.passed();
		//comment = "distribute-fluids-from-node-to-tube";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

		time.reset();
	Step9UpdateTubeMpos::update_tube_mpos_according_to_proportion(state);
		state.measured.time_taken_by_each_step[9] += time.passed();
		//comment = "update-tube-mpos-according-to-proportion";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

		time.reset();
	
	//~ int count_tube = 0;
	//~ for(const auto& tube: state.tubes)
	//~ {
		//~ double his = 0;
		//~ for(const auto x: tube.mpos)
		//~ {
			//~ if(x > 1.0 || x < 0)
			//~ {
				//~ std::cerr << "WARNing - non-prop value";
			//~ }
			//~ if(x <= his)
			//~ {
				//~ std::cerr << "Meniscus not in proper order, at tube: " << count_tube << " step-id=" << state.reference.id_step << std::endl;
				//~ for(auto x: tube.mpos)
				//~ {
					//~ std::cout << x << ", ";
				//~ }
			//~ }
			//~ his = x;
		//~ }
		
		//~ ++ count_tube;
	//~ }
	
	Step10Measure::measure(state);
		state.measured.time_taken_by_each_step[10] += time.passed();
		//comment = "measure";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;
	
}
