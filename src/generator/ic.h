#ifndef GENERATOR_IC_H
#define GENERATOR_IC_H

#include "global/dst.h"
#include <utility>

namespace generator
{
	class Ic
	{

	public:

	static std::pair<std::vector<nst::Node>, std::vector<nst::Tube>>
	square_lattice(int tube_nrows, int tube_ncols);
	};


}
#endif
