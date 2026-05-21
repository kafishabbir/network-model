#ifndef IC_GEOMETRY_MULTIPLE_TUBES_BETWEEN_NODES_H
#define IC_GEOMETRY_MULTIPLE_TUBES_BETWEEN_NODES_H

#include "ic/geometry-base.h"

namespace ic
{
	class GeometryMultipleTubesBetweenNodes
	{
	public:
		static type_pair_nodes_tubes network_geometry_real(
			const int n_tube_rows,
			const int n_tube_cols,
			const int id_fluid_inject,
			const double constant_length_scale
		);
	};
}

#endif
