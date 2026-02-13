#ifndef NST_NODE_H
#define NST_NODE_H

#include "nst/tank.h"

namespace nst
{
	class Node
	{
		struct Calculated
		{
			double pressure;
			nst::Tank tank;
			double volume_fluid_flow_out;
			std::vector<int> connections_id_tube_v;
			std::vector<int> flow_out_id_tube_v;
			bool is_fluid_added_to_this_node;
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
		int id_fluid_inject;

		Calculated calculated;
		Visual visual;

		Node();
	};
}



#endif
