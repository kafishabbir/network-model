#ifndef IC_GEOMETRY_FLOW_H
#define IC_GEOMETRY_FLOW_H

#include "ic/geometry-base.h"

namespace ic
{
	class GeometryFlow
	{
		public:
		
		static std::tuple<double, double, double, double> find_min_max_coordinates(
			const nst::Nodes& nodes
		);
		
		static type_pair_nodes_tubes network_geometry(
			const int n_tube_rows,
			const int n_tube_cols,
			const int id_fluid_inject,
			const double constant_radius_contrast,
			const double constant_length_scale,
			const double n_periods,
			const bool is_skewed
		);
		
		static type_pair_nodes_tubes network_geometry_const_porosity(
			const int n_tube_rows,
			const int n_tube_cols,
			const int id_fluid_inject,
			const double constant_radius_contrast,
			const double constant_length_scale,
			const double n_periods,
			const bool is_skewed
		);
		
		
		static type_pair_nodes_tubes network_geometry_random_radius(
			const int n_tube_rows,
			const int n_tube_cols,
			const int id_fluid_inject,
			const double constant_radius_contrast,
			const double constant_length_scale
		);
		
		
		static type_pair_nodes_tubes network_geometry_const_porosity_random_radius(
			const int n_tube_rows,
			const int n_tube_cols,
			const int id_fluid_inject,
			const double constant_radius_contrast,
			const double constant_length_scale
		);
	};
}

#endif
