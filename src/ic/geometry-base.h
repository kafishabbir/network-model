#ifndef IC_GEOMETRY_BASE_H
#define IC_GEOMETRY_BASE_H

#include "nst/node.h"
#include "nst/tube.h"

namespace ic
{
	typedef std::pair<std::vector<nst::Node>, std::vector<nst::Tube>>type_pair_nodes_tubes;

    class GeometryBase
    {
		static std::vector<nst::Node> rectangular_nodes(
			const int n_tube_rows,
			const int n_tube_cols
		);

		static std::vector<nst::Tube> rectangular_tubes(
			const int n_tube_rows,
			const int n_tube_cols
		);

        public:
        static type_pair_nodes_tubes rectangular(
			const int n_tube_rows,
			const int n_tube_cols
		);
    };
}

#endif
