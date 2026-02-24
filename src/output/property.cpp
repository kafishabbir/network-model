#include "output/property.h"

output::Property::Property():
	tube_radius_min(0.02),
	tube_radius_max(0.10),
	largest_angle_tube_project_on_node(decl::pi / 2.0),
	vector_image_draw_shape_perimeter(true),
	vector_image_label_node_detail(true),
	vector_image_label_tube_detail(true)
{}
