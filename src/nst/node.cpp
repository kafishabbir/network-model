#include "nst/node.h"


nst::Node::Calculated::Calculated():
	pressure(0),
	tank(),
	flow_out_id_tube_v(),
	volume_fluid_flow_out(0),
	is_fluid_injected_from_external_to_this_node(false),
	id_symmetric_solver(-1)
{}


double nst::Node::Visual::distance(const Node& node) const
{
	const double dx = node.visual.x - x;
	const double dy = node.visual.y - y;

	return std::sqrt(dx * dx + dy * dy);
}

double nst::Node::Visual::relative_angle(const Node& node) const
{
	const double x1 = x;
	const double y1 = y;

	const double x2 = node.visual.x;
	const double y2 = node.visual.y;

	const double delta_x = x2 - x1;
	const double delta_y = y2 - y1;

	return std::atan2(delta_y, delta_x) * 180 / std::acos(-1);
}


nst::Node::Node():
	x(-1),
	y(-1),
	pressure(-1),
	is_open_boundary(false),
	id_fluid_inject(-1),
	reference(),
	calculated()
{}
