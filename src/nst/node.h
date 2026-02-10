#ifndef NST_NODE_H
#define NST_NODE_H

#include <cmath>
#include <vector>
#include "nst/tank.h"
namespace nst
{
	class Node
	{
		struct Reference
		{
			std::vector<int> connections_tube_id_v;
			std::vector<bool> is_flow_out_of_node_into_tube_v;
		};


		struct Calculated
		{
			nst::Tank tank;
		};


		struct Visual
		{
			double x;
			double y;
			double radius;

			double distance(const Node& node) const;
			double relative_angle(const Node& node) const;
		};

	public:
		double x;
		double y;
		double pressure;
		bool is_open_boundary;
		Reference reference;
		Calculated calculated;
		Visual visual;


		Node();
	};
}



#endif
