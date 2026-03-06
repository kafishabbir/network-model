#include "dst/state.h"


dst::State::State(const std::pair<nst::Nodes, nst::Tubes>& p):
	nodes(p.first),
	tubes(p.second)
{}


dst::State::Measured::Measured():
	time_elapsed(0),
	
	fluid_added(),
	fluid_evacuated()
	
{}


dst::State::Reference::Reference():
	id_step(-1),
	comment("comment=null")
{}



dst::State::Calculated::Calculated():
	time_step(-1),
	fluid_added(),
	fluid_evacuated()
{}




