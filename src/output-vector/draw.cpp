#include "output-vector/draw.h"
#include "output-vector/tikz.h"

std::string output_vector::Draw::mpos_horizontal_rectangles(
	const nst::Tube& tube,
	const output::Property& visual_property,
	const std::vector<std::string>& colors
)
{
	const int n = tube.visual.mpos.size();
	std::stringstream ss;
	for(int i = 1; i < n; ++ i)
	{
		const auto& color = colors[(i + tube.id_fluid_first + 1) % 2];
		const double x1 = tube.visual.mpos[i - 1];
		const double y1 = tube.visual.radius;
		const double x2 = tube.visual.mpos[i];
		const double y2 = - tube.visual.radius;

		ss << Tikz::rectangle(color, x1, y1, x2, y2) << '\n';
	}
	return ss.str();
}


std::string output_vector::Draw::draw_tube(
	const nst::Tube& tube,
	const dst::State& state,
	const output::Property& visual_property,
	const std::vector<std::string>& colors
)
{
	const auto& node_first = state.nodes[tube.id_node_first];
	const auto& node_second = state.nodes[tube.id_node_second];

	return Tikz::scope_shift_and_rotate(
		node_first.visual.x,
		node_first.visual.y,
		node_first.visual.relative_angle(node_second),
		mpos_horizontal_rectangles(tube, visual_property, colors)
	);
}

std::string output_vector::Draw::draw_tubes(
	const dst::State& state,
	const output::Property& visual_property,
	const std::vector<std::string>& colors
)
{
	std::stringstream ss;
	for(const auto& tube: state.tubes)
	{
		ss << draw_tube(tube, state, visual_property, colors) << '\n';
	}

	return ss.str();
}

std::string output_vector::Draw::draw_node(
	const nst::Node& node,
	const output::Property& visual_property,
	const std::vector<std::string>& colors
)
{
	return Tikz::circle(
		node.visual.x, 
		node.visual.y,
		node.visual.radius, 
		colors[node.calculated.type_fluid_contact]
	);
}

std::string output_vector::Draw::draw_nodes(
	const dst::State& state,
	const output::Property& visual_property,
	const std::vector<std::string>& colors
)
{
	std::stringstream ss;
	for(const auto& node: state.nodes)
	{
		ss << draw_node(node, visual_property, colors) << '\n';
	}

	return ss.str();
}
