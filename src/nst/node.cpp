#include "nst/node.h"

double nst::Node::distance(const Node& node) const
{
	const double dx = node.x - x;
	const double dy = node.y - y;

	return std::sqrt(dx * dx + dy * dy);
}

double nst::Node::relative_angle(const Node& node) const
{
	const double x1 = x;
	const double y1 = y;

	const double x2 = node.x;
	const double y2 = node.y;

	const double delta_x = x2 - x1;
	const double delta_y = y2 - y1;

	return std::atan2(delta_y, delta_x) * 180 / std::acos(-1);
}
