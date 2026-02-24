#include "output-vector/label-tube.h"




std::string visualize::Flow::label_tube_middle(const nst::Tube& tube, const int id_tube, const output::Property& visual_property)
{
	const double lv = tube.visual.length;
	std::stringstream ss;

	if(visual_property.label_id_tube)
	{
		ss << "$b_{" << id_tube << "}$";
	}

	return visualize::Draw::node(
		lv / 2,
		0,
		ss.str()
	);
}

std::string visualize::Flow::label_tube_below(const nst::Tube& tube, const output::Property& visual_property)
{
	const double rv = tube.visual.radius;
	const double lv = tube.visual.length;

	std::stringstream ss;

	int i = tube.id_node_first;
	int j = tube.id_node_second;

	double q = tube.calculated.flow_rate;
	double arrow_begin = lv/8;
	double arrow_end = lv*3/8;
	double q_pos = lv*3/8;
	if(q < 0)
	{
		std::swap(i, j);
		arrow_begin = lv*7/8;
		arrow_end = lv*5/8;
		q = std::abs(q);
		q_pos = lv*5/8;
	}

	if(visual_property.label_tube_flow_rate)
	{
		ss << visualize::Draw::arrow(arrow_begin, arrow_end, -1.75 * rv) << '\n';

		std::stringstream ss_node;
		ss_node << "$" << "q_{" << i << j << "}=" << Draw::num(q) << "$";

		ss << visualize::Draw::node(q_pos, - 2 * rv, ss_node.str());
	}

	return ss.str();
}



std::string visualize::FlowVerificationLabel::label_tube_above(const nst::Tube& tube, const output::Property& visual_property)
{
	const double x_proportion_location = 0.5;
	//const double rv = tube.visual.radius;
	const double lv = tube.visual.length;

	std::stringstream ss;

	if(visual_property.label_tube_direction)
	{
		ss << "$tube_{" << tube.id_node_first << ", " << tube.id_node_second << "}$, ";

		ss << "$a=" << Draw::num(tube.calculated.resistance_coefficient) << "$, ";

		ss << "$P_c=" << Draw::num(tube.calculated.capillary_pressure_magnitude) << "$, \\\\ ";
	}

	if(visual_property.label_tube_velocity)
	{
		ss << "$v = " << Draw::num(tube.calculated.velocity) << "$, ";
	}
	if(visual_property.label_tube_time)
	{
		ss << "$t = " << Draw::num(tube.calculated.time) << "$, \\\\";
		if(tube.calculated.is_time_min)
		{
			ss << " MIN HERE,\\\\";
		}
	}
	if(visual_property.label_tube_details)
	{
		ss << "mpos=(";
		if (tube.mpos.empty()) {
			ss << "none";
		} else {
			for (size_t i = 0; i < tube.mpos.size(); ++i) {
				if (i > 0) ss << ", ";
				ss << "$" << Draw::num(tube.mpos[i]) << "$";
			}
		}
		ss << ")\n\\\\";
		ss << "length-disp-p=$" << Draw::num(tube.calculated.length_displacement_p) << "$\n\\\\";
		ss << "vol-disp=$" << Draw::num(tube.calculated.volume_displacement) << "$\n\\\\";
		ss << "id-sink=" << tube.calculated.id_node_sink << "\n\\\\";
		ss << "tank-pour=" << Draw::str(tube.calculated.tank_pour_into_node) << "\n\\\\";
		ss << "add-prop=$" << Draw::num(tube.calculated.add_proportion) << "$\n";
	}
	if(visual_property.label_tube_radius)
	{
		ss << "$r=" << Draw::num(tube.radius) << "$, ";
	}
	if(visual_property.label_tube_length)
	{
		ss << "$l=" << Draw::num(tube.length) << "$, \\\\ ";
	}

	return visualize::Draw::node_long(
		lv * x_proportion_location,
		0.03,
		ss.str()
	);
}


std::string visualize::FlowVerificationLabel::code_tubes_labels(const nst::State& state, const output::Property& visual_property)
{
	const auto& tubes = state.tubes;
	const int n_tubes = tubes.size();
	std::stringstream ss;
	for(int i = 0; i < n_tubes; ++ i)
	{
		ss << code_tube(state, i, visual_property) << '\n';
	}

	return ss.str();
}


std::string visualize::FlowVerificationLabel::code_nodes_labels(const nst::State& state, const output::Property& visual_property)
{
	const auto& nodes = state.nodes;
	const int n_nodes = nodes.size();
	std::stringstream ss;
	for(int i = 0; i < n_nodes; ++ i)
	{
		ss << code_node_label(nodes[i], i, visual_property) << '\n';
	}

	return ss.str();
}


