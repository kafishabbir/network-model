#ifndef NST_NODE_H
#define NST_NODE_H

#include <cmath>
#include <vector>
namespace nst
{
	class Node
	{
		struct Visual
		{
			double x;
			double y;
			double radius;
		};

	public:
		double x;
		double y;
		double radius;
		double pressure;
		bool is_open_boundary;

		Visual visual;

		double visual_distance(const Node& node) const;
		double relative_angle(const Node& node) const;
	};
}

typedef std::vector<nst::Node> Nodes;

#endif
