#ifndef IC_GEOMETRY_BASE_H
#define IC_GEOMETRY_BASE_H

#include "global/dst.h"

namespace ic
{
	typedef std::pair<dst::Nodes, std::vector<nst::Tube>>type_pair_nodes_tubes;

    class GeometryBase
    {
		static dst::Nodes rectangular_nodes(
			const int n_tube_rows,
			const int n_tube_cols,
			const int id_fluid_inject,
			const int id_fluid_evacuate
		);

		static std::vector<nst::Tube> rectangular_tubes(
			const int n_tube_rows,
			const int n_tube_cols,
			const int id_fluid_saturate
		);

        public:
        static type_pair_nodes_tubes rectangular(
			const int n_tube_rows,
			const int n_tube_cols,
			const int id_fluid_inject
		);
    };
}

#endif
