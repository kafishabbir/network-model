#include "output-vector/label-tube.h"
#include "output-vector/tikz.h"
#include "output-vector/draw.h"


std::pair<int, int> output_vector::LabelTube::id_node_flow_direction(
	const int id_node_first, 
	const int id_node_second, 
	const double flow_rate
)
{
	if(flow_rate < 0)
	{
		return {id_node_second, id_node_first};
	}
	return {id_node_first, id_node_second};
}

std::pair<double, double> output_vector::LabelTube::pos_arrow_flow_direction(
	const double visual_length, 
	const double flow_rate
)
{
	if(flow_rate < 0)
	{
		return {visual_length * 7/8, visual_length * 5/8};
	}
	return {visual_length/8, visual_length * 3/8};
}

std::string output_vector::LabelTube::label_id_tube(const int id_tube)
{
	std::stringstream ss;
	ss << "$b_{" << id_tube << "}$";
	return ss.str();
}

std::string output_vector::LabelTube::label_ij_flow_rate(
	const int i, 
	const int j, 
	const double flow_rate
)
{
	std::stringstream ss;
	ss << "$q_{" << i << j << "}=" << output_vector::LabelTube::s(flow_rate) << "$";
	return ss.str();
}


std::string output_vector::LabelTube::label_tube_basic(
	const nst::Tube& tube, 
	const int id_tube,
	const nst::State& state
)
{	
	// Get flow direction node IDs
	auto [i, j] = id_node_flow_direction(
		tube.id_node_first, 
		tube.id_node_second,  
		tube.calculated.flow_rate
	);
	
	// Get arrow positions
	auto [arrow_begin, arrow_end] = pos_arrow_flow_direction(
		tube.visual.length, 
		tube.calculated.flow_rate
	);
	
	const double q_pos = (arrow_begin + arrow_end) / 2;
	const double q = std::abs(tube.calculated.flow_rate);
	const double radius = tube.visual.radius;

	std::stringstream ss;
	
	// Tube number in the middle
	ss << Tikz::node(tube.visual.length / 2, 0, label_id_tube(id_tube)) << '\n';
	
	// Arrow
	ss << Tikz::arrow(arrow_begin, arrow_end, -1.75 * radius) << '\n';
	
	// Flow rate label
	ss << Tikz::node(q_pos, -2 * radius, label_ij_flow_rate(i, j, q)) << '\n';
	
	const auto& node_first = state.nodes[tube.id_node_first];
	const auto& node_second = state.nodes[tube.id_node_second];
	
	return Tikz::scope_shift_and_rotate(
		node_first.visual.x,
		node_first.visual.y,
		node_first.visual.relative_angle(node_second),
		ss.str()
	);
}

std::string output_vector::LabelTube::label_tube_details(
	const nst::Tube& tube,
	const nst::State& state
)
{
	std::stringstream ss;
	
	ss << "$(" << tube.id_node_first << "-" << tube.id_node_second << ")$, ";
	ss << "r=$" << s(tube.radius) << "$, ";
	ss << "\n\\\\";
	
	ss << "mpos=" << v(tube.mpos) << ", "; 
	ss << "\n\\\\";
	
	ss << "l=$" << s(tube.length) << "$, ";
	ss << "id-1st-fluid=" << tube.id_fluid_first << ", ";
	ss << "area=$" << s(tube.area()) << "$, ";
	ss << "\n\\\\";
	
	ss << "vol=$" << s(tube.volume()) << "$, ";
	ss << "resis=$" << s(tube.calculated.resistance_coefficient) << "$, ";
	ss << "$p_c=" << s(tube.calculated.capillary_pressure_magnitude) << "$, ";
	ss << "\n\\\\";
		
	ss << "v=$" << s(tube.calculated.velocity) << "$, ";
	ss << "t=$" << s(tube.calculated.time) << "$" << (tube.calculated.is_time_min ? "-MIN" : "") << ", ";
	ss << "prop-l-disp=$" << s(tube.calculated.length_displacement_p) << "$, ";
	ss << "\n\\\\";
	
	ss << "vol-disp=$" << s(tube.calculated.volume_displacement) << "$, ";
	ss << "add-prop=$" << s(tube.calculated.add_proportion) << "$, ";
	ss << "id-sink=" << tube.calculated.id_node_sink << ", ";
	ss << "\n\\\\";
	
	ss << "tank-pour=" << tube.calculated.tank_pour_into_node.str() << ".";
	
	// Create the text node
	std::string text_node = Tikz::node_long(
		tube.visual.length * 0.5,
		0.03,
		ss.str()
	);
	
	const auto& node_first = state.nodes[tube.id_node_first];
	const auto& node_second = state.nodes[tube.id_node_second];
	
	return Tikz::scope_shift_and_rotate(
		node_first.visual.x,
		node_first.visual.y,
		node_first.visual.relative_angle(node_second),
		text_node
	);
}

std::string output_vector::LabelTube::basic(const nst::State& state)
{
	const int n_tubes = state.tubes.size();
	
	std::stringstream ss;
	for(int i = 0; i < n_tubes; ++i)
	{
		ss << label_tube_basic(state.tubes[i], i, state) << '\n';
	}
	
	return ss.str();
}

std::string output_vector::LabelTube::details(const nst::State& state)
{
	std::stringstream ss;
	for(const auto& tube : state.tubes)
	{
		ss << label_tube_details(tube, state) << '\n';
	}
	
	return ss.str();
}
