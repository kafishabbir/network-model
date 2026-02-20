#include "program/flow-in-periodic-medium.h"
#include "program/debug-flow.h"
#include "program/function-trial.h"

int main()
{
	program::FlowInPeriodicMedium::run();
	//program::DebugFlow::run();

	//program::FunctionTrial trial;
    //trial.flow();
	return 0;
}
