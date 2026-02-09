#include "visualize/property.h"

visualize::Property::Property():
	colors_str_v({"cw", "cnw"}),
	tube_radius_min(0.02),
	tube_radius_max(0.10),
	largest_angle_tube_project_on_node(decl::pi / 2.0),
	draw_node_perimeter(true),
	label_node_id(true),
	label_node_pressure(true),
	label_tube_id(true),
	label_tube_radius(true),
	label_tube_length(true),
	label_tube_flow_rate(true)
{}
