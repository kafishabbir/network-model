#include "dst/system.h"


dst::System::System(const std::pair<Parameter, State>& pair):
	parameter(pair.first),
	state(pair.second)
{}
