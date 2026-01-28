#ifndef NST_NODE_H
#define NST_NODE_H

#include <cmath>
#include <vector>
namespace nst
{
	class Node
	{
	public:
		double x;
		double y;
		double radius;
		double pressure;
		bool is_open_boundary;

		std::vector<double> radii_of_tubes_attached_to_this_node;
		double distance(const Node& node) const;
		double relative_angle(const Node& node) const;
	};
}

typedef std::vector<nst::Node> Nodes;

#endif
