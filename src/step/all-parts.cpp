#include "step/all-parts.h"


#include "step/part01-reference.h"
#include "step/part02-pressure.h"
#include "step/part03-velocity.h"
#include "step/part04-time.h"
#include "step/part05-displacement.h"
#include "step/part06-pour.h"
#include "step/part07-inject.h"
#include "step/part08-distribute.h"
#include "step/part09-displace.h"
#include "step/part10-measure.h"


void step::AllParts::run_single_time_step(
	dst::System& system
)
{
	//auto& comment = state.reference.comment;

	//int j = 0;
	utility::Time time;
	

	step::Part01Reference::assign_resistance_and_capillary_pressure_to_tubes(state);
		system.measured.time_taken_by_each_step[1] += time.passed();
		//comment = "assign-resistance-and-capillary-pressure-to-tubes";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

	step::Part02Pressure::generate_symmetric_linear_equations_and_assign_pressure_to_node(
		state,
		is_solver_prepared,
		solver
	);
		system.measured.time_taken_by_each_step[2] += time.passed();
		//comment = "generate-linear-equations-and-assign-pressure-to-node";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

	step::Part03Velocity::calculate_and_assign_flow_rate_and_velocity_to_tube(state);
		system.measured.time_taken_by_each_step[3] += time.passed();
		//comment = "calculate-and-assign-flow-rate-and-velocity-to-tube";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

	step::Part04Time::assign_time_step_to_state(state);
		system.measured.time_taken_by_each_step[4] += time.passed();
		//comment = "assign-time-step-to-state";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

	step::Part05Displacement::assign_volume_length_displacement(state);
		system.measured.time_taken_by_each_step[5] += time.passed();
		//comment = "assign-volume-length-displacement";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

	step::Part06Pour::pour_from_tubes_to_node_tank(state);
		system.measured.time_taken_by_each_step[6] += time.passed();
		//comment = "pour-from-tubes-to-node-tank";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

	step::Part07Inject::inject_and_evacuate_fluid_from_system(state);
		system.measured.time_taken_by_each_step[7] += time.passed();
		//comment = "inject-and-evacuate-fluid-from-system";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

	step::Part08Distribute::distribute_fluids_from_node_to_tube(state);
		system.measured.time_taken_by_each_step[8] += time.passed();
		//comment = "distribute-fluids-from-node-to-tube";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

	step::Part09Displace::update_tube_mpos_according_to_proportion(state);
		system.measured.time_taken_by_each_step[9] += time.passed();
		//comment = "update-tube-mpos-according-to-proportion";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;

	
	step::Part10Measure::measure(state);
		system.measured.time_taken_by_each_step[10] += time.passed();
		//comment = "measure";
		//states.push_back(state);
		//std::cout << "here" << j++ << std::endl;
	
}
