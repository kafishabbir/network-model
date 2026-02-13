#include "visualize/flow-verification-label.h"


std::string visualize::FlowVerificationLabel::node_details(const nst::Node& node)
{
    std::stringstream ss;

    //ss << "  Position: (" << Draw::num(node.x) << ", " << Draw::num(node.y) << ")\n\\\\";
    //ss << "  Pressure: $" << Draw::num(node.pressure) << "$\n\\\\";
    ss << "open boundary: " << (node.is_open_boundary ? "true" : "false") << "\n\\\\";
    ss << "id-fluid-inj: " << node.id_fluid_inject << "\n\\\\";
    ss << "Tank: " << Draw::str(node.calculated.tank) << "\n\\\\";
    ss << "total-v-out=$" << Draw::num(node.calculated.volume_fluid_flow_out) << "$\n\\\\";

    // Connection tubes
    ss << "connected-id-tubes:(";
    if (node.calculated.connections_id_tube_v.empty()) {
        ss << "none";
    } else {
        for (size_t i = 0; i < node.calculated.connections_id_tube_v.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << node.calculated.connections_id_tube_v[i];
        }
    }
    ss << ")\n\\\\";

    // Flow out tubes
    ss << "flow-id-tubes: ";
    if (node.calculated.flow_out_id_tube_v.empty()) {
        ss << "none";
    } else {
        for (size_t i = 0; i < node.calculated.flow_out_id_tube_v.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << node.calculated.flow_out_id_tube_v[i];
        }
    }
    ss << "\n\\\\";

    ss << "fluid-injected:" << (node.calculated.is_fluid_added_to_this_node ? "true" : "false") << "\n\\\\";

    return ss.str();
}

std::string visualize::FlowVerificationLabel::code_node_label(const nst::Node& node, const int id_node, const visualize::Property& visual_property)
{
	const double x = node.visual.x;
	const double y = node.visual.y;
	//const double radius = node.visual.radius;
	std::stringstream ss;

	if(visual_property.label_id_node)
	{
		std::stringstream ss_node;
		ss_node << "$\\nu_{" << id_node << "}$";
		ss << visualize::Draw::node(x, y, ss_node.str()) << '\n';
	}
	if(visual_property.label_node_pressure)
	{
		std::stringstream ss_pressure;
		ss_pressure << "$p=" << Draw::num(node.calculated.pressure) << "$";
		ss << visualize::Draw::node(x, y + 0.01, ss_pressure.str()) << '\n';
	}
	if(visual_property.label_node_details)
	{
		ss << visualize::Draw::node_long(x+0.03, y - 0.03, node_details(node)) << '\n';
	}
	return ss.str();
}


std::string visualize::FlowVerificationLabel::label_tube_above(const nst::Tube& tube, const visualize::Property& visual_property)
{
	const double x_proportion_location = 0.5;
	//const double rv = tube.visual.radius;
	const double lv = tube.visual.length;

	std::stringstream ss;

	if(visual_property.label_tube_direction)
	{
		ss << "$p_{" << tube.id_node_first << tube.id_node_second << "} = " << Draw::num(tube.calculated.capillary_pressure_magnitude) << "$, \\\\ ";
	}
	if(visual_property.label_tube_radius)
	{
		ss << "$r=" << Draw::num(tube.radius) << "$, ";
	}
	if(visual_property.label_tube_length)
	{
		ss << "$l=" << Draw::num(tube.length) << "$, \\\\ ";
	}
	if(visual_property.label_tube_velocity)
	{
		ss << "$v = " << Draw::num(tube.calculated.velocity) << "$, ";
	}
	if(visual_property.label_tube_time)
	{
		ss << "$t = " << Draw::num(tube.calculated.time) << "$, ";
		if(tube.calculated.is_time_min)
		{
			ss << "\\\\ MIN HERE,";
		}
	}
	return visualize::Draw::node_long(
		lv * x_proportion_location,
		0.03,
		ss.str()
	);
}

std::string visualize::FlowVerificationLabel::code_tube(const nst::State& state, const int id_tube, const visualize::Property& visual_property)
{
	const auto& tube = state.tubes[id_tube];
	const auto& node_first = state.nodes[tube.id_node_first];
	const auto& node_second = state.nodes[tube.id_node_second];

	return visualize::Draw::scope_shift_and_rotate(
		node_first.visual.x,
		node_first.visual.y,
		node_first.visual.relative_angle(node_second),
		label_tube_above(tube, visual_property)
	);
}

std::string visualize::FlowVerificationLabel::code_tubes_labels(const nst::State& state, const visualize::Property& visual_property)
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


std::string visualize::FlowVerificationLabel::code_nodes_labels(const nst::State& state, const visualize::Property& visual_property)
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


