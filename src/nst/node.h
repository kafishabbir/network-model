#ifndef NST_NODE_H
#define NST_NODE_H

#include "nst/tank.h"

namespace nst
{
	class Node
	{
		struct Reference
		{
			std::vector<int> connections_id_tube_v;
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

		struct Calculated
		{
			double pressure;
			nst::Tank tank;
			std::vector<int> flow_out_id_tube_v;
			double volume_fluid_flow_out;
			bool is_fluid_injected_from_external_to_this_node;
			Calculated();
		};

	public:
		double x;
		double y;
		double pressure;
		bool is_open_boundary;
		int id_fluid_inject;

		Reference reference;
		Calculated calculated;
		Visual visual;

		Node();
	};
}



#endif
