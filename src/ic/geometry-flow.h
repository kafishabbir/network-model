#ifndef IC_GEOMETRY_FLOW_H
#define IC_GEOMETRY_FLOW_H

#include "ic/geometry-base.h"

namespace ic
{
    class GeometryFlow
    {
		static std::tuple<double, double, double, double> find_min_max_coordinates(
			const dst::Nodes& nodes
		);

        public:
        static type_pair_nodes_tubes network_geometry(
			const int n_tube_rows,
			const int n_tube_cols,
			const int id_fluid_inject,
			const double constant_radius_contrast,
			const double constant_length_scale,
			const double n_periods
		);
    };
}

#endif
