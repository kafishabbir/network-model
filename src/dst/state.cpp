#include "dst/state.h"

dst::State::Measured::Measured():
	time_elapsed(0),
	time_taken_by_solving_linear_equations(0),
	time_taken_by_each_step(11),
	
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




