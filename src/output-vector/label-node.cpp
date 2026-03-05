#include "output-vector/label-node.h"
#include "output-vector/tikz.h"

std::string output_vector::LabelNode::label_node_details(const nst::Node& node)
{
	std::stringstream ss;
	
	ss << "coordinate=$(" << s(node.x) << ", " << s(node.y) << ")$" << "\n\\\\";
	ss << "id-symm=" << node.calculated.id_symmetric_solver << "\n\\\\";
	ss << "open-bound=" << (node.is_open_boundary ? "true" : "false") << "\n\\\\";
	ss << "contact=" << node.calculated.type_fluid_contact << "\n\\\\";
	
	if(node.is_open_boundary)
	{
		ss << "is-inlet=" << (node.is_inlet ? "true" : "false") << "\n\\\\";
		ss << "is-fluid-injected=" << (node.calculated.is_fluid_injected_from_external_to_this_node ? "true" : "false") << "\n\\\\";
		ss << "bound-pressure=" << s(node.pressure) << "\n\\\\";
		ss << "id-fluid-inject=" << node.id_fluid_inject << "\n\\\\";
	}
	
	ss << "connected-tubes=" << v(node.reference.connections_id_tube_v) << "\n\\\\";
	ss << "tank=" << node.calculated.tank.str() << "\n\\\\";
	// ss << "calc-pressure=" << s(node.calculated.pressure) << "\n\\\\";
	ss << "flow-out=" << s(node.calculated.volume_fluid_flow_out) << "\n\\\\";
	ss << "flow-out=" << v(node.calculated.flow_out_id_tube_v);

	return Tikz::node_long(node.visual.x + 0.03, node.visual.y + 0.01, ss.str());
}



std::string output_vector::LabelNode::details(const dst::State& state)
{
	std::stringstream ss;

	for(const auto& node: state.nodes)
	{
		ss << label_node_details(node) << '\n';
	}
	
	return ss.str();
}

std::string output_vector::LabelNode::label_node_basic(
	const nst::Node& node,
	const int id_node
)
{
	std::stringstream ss1, ss2, ss_final;
	ss1 << "$p_{" << id_node << "}$";
	ss2 << "$" << s(node.calculated.pressure) << "$";
	
	ss_final << Tikz::node(node.visual.x, node.visual.y+0.01, ss1.str()) << '\n';
	ss_final << Tikz::node(node.visual.x, node.visual.y-0.003, ss2.str()) << '\n';
	return ss_final.str();
}


std::string output_vector::LabelNode::basic(const dst::State& state)
{
	const int n_nodes = state.nodes.size();
	
	std::stringstream ss;
	for(int i = 0; i < n_nodes; ++ i)
	{
		ss << label_node_basic(state.nodes[i], i) << '\n';
	}
	
	return ss.str();
}
