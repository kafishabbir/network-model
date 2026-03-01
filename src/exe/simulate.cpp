#include "program/flow-in-periodic-medium.h"
#include "program/debug-flow.h"
#include "program/function-trial.h"
#include "program/permeability.h"

int main()
{
	program::Permeability::run();
	//program::FlowInPeriodicMedium::run();
	//program::DebugFlow::run();

	//program::FunctionTrial trial;
	//trial.flow();
	return 0;
}
