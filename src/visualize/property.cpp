#include "visualize/property.h"

visualize::Property::Property():
	colors_str_v({"cw", "cnw"}),
	tube_radius_min(0.02),
	tube_radius_max(0.10),
	largest_angle_tube_project_on_node(decl::pi / 2.0),
	draw_node_perimeter(true),

	label_id_node(false),
	label_node_pressure(false),
	label_id_tube(false),
	label_tube_radius(false),
	label_tube_length(false),
	label_tube_flow_rate(false),
	label_tube_direction(false),
	label_capillary_pressure(false),
	label_tube_velocity(false),
	label_tube_time(false),
	label_node_details(false),
	label_tube_details(false)
{}
