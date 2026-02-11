#ifndef NST_NODE_H
#define NST_NODE_H

#include "nst/tank.h"

namespace nst
{
	class Node
	{
		struct Calculated
		{
			nst::Tank tank;
			double volume_fluid_out;
			std::vector<int> connections_id_tube_v;
			std::vector<bool> is_flow_out_id_tube_v;
			std::vector<int> flow_out_sorted_id_tube_v;
			bool is_evacuate_fluid;
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
		int fluid_to_input;

		Calculated calculated;
		Visual visual;

		Node();
	};
}



#endif
