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
			square_lattice(const int n_rows_tube, const int n_cols_tube);
	};


}
#endif
