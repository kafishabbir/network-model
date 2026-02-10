#ifndef IC_MENU_H
#define IC_MENU_H

#include "ic/geometry-rand.h"
#include "ic/geometry-flow.h"

namespace ic
{
    class Menu
    {
        public:

		static type_pair_nodes_tubes network_geometry_base(
			const int n_tube_rows,
			const int n_tube_cols
		);

		static type_pair_nodes_tubes network_geometry_flow();

		static type_pair_nodes_tubes network_geometry_rand();
    };
}

#endif
