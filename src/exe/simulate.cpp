#include "program/flow-in-periodic-medium.h"
#include "program/debug-flow.h"
#include "program/function-trial.h"
#include "program/permeability.h"
#include "program/flow-with-divided-tubes.h"
#include "program/overlapping-tubes-of-differing-radii.h"

#include <omp.h>
#include <thread>

/**
 * @file exe/simulate.cpp
 * @brief executable that generates solutions
 * 
 * Choose program based on commenting and uncommenting lines
 * Compiles into an executable
 */


/**
 * @brief main function of the executable
 * 
 * This function runs the chosen simulation program
 * Choose by commenting and uncommenting
 * 
 * @return returns int 0 on successful execution
 */
 
int main()
{
	omp_set_num_threads(3);
	
	//program::Permeability::run();
	program::FlowInPeriodicMedium::run();
//	program::FlowWithDividedTubes::run();
//	program::OverlappingTubesOfDifferingRadii::run();
	//program::DebugFlow::run();
 
	//program::FunctionTrial trial;
	//trial.flow();
	return 0;
}
