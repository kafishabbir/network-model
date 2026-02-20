#include "visualize/raster.h"

const std::vector<visualize::Cairo::Color> visualize::Raster::colors_v =
{
	visualize::Cairo::Color::grey_dark,
	visualize::Cairo::Color::grey_light
};

void visualize::Raster::code_node(
    Cairo& cairo,
    const nst::Node& node,
    const visualize::Property& visual_property
)
{
    double x = node.visual.x;
    double y = node.visual.y;
    double radius = node.visual.radius;

    if(visual_property.draw_node_perimeter)
    {
        cairo.circle(x, y, radius, Cairo::Color::grey);
    }
}


void visualize::Raster::code_tube(
    Cairo& cairo,
    const nst::State& state,
    int id_tube,
    const visualize::Property& visual_property
)
{
    const auto& tube = state.tubes[id_tube];
    const auto& node_first = state.nodes[tube.id_node_first];
    const auto& node_second = state.nodes[tube.id_node_second];

	cairo.begin_shift_rotate(
		node_first.visual.x,
		node_first.visual.y,
		node_first.visual.relative_angle_radians(node_second)
	);
		const std::vector<double>& v = tube.visual.mpos;
		const int id_fluid_first = tube.id_fluid_first;
		const double radius = tube.visual.radius;

		const int n = v.size();
		for(int i = 1; i < n; ++ i)
		{
			const auto& color = colors_v[(i + id_fluid_first + 1) % 2];
			const double x = v[i - 1];
			const double length = v[i] - x;

			cairo.rectangle(
				x,
				-radius,
				length,
				2.0 * radius,
				color
			);
		}
	cairo.end_shift_rotate();
}

void visualize::Raster::code_nodes(
    Cairo& cairo,
    const nst::State& state,
    const visualize::Property& visual_property
)
{
    const auto& nodes = state.nodes;
    int n_nodes = nodes.size();
    for(int i = 0; i < n_nodes; ++ i)
    {
        code_node(cairo, nodes[i], visual_property);
    }
}

void visualize::Raster::code_tubes(
    Cairo& cairo,
    const nst::State& state,
    const visualize::Property& visual_property
)
{
    const auto& tubes = state.tubes;
    int n_tubes = tubes.size();
    for(int i = 0; i < n_tubes; ++ i)
    {
        code_tube(cairo, state, i, visual_property);
    }
}

std::pair<double, double> visualize::Raster::xy_max_nodes(
	const dst::Nodes& nodes
)
{
	double x_max = nodes.front().visual.x;
	double y_max = nodes.front().visual.y;

	for(const auto& node: nodes)
	{
		x_max = std::max(x_max, node.visual.x);
		y_max = std::max(y_max, node.visual.y);
	}

	return {x_max, y_max};
}


void visualize::Raster::flow(
    const nst::State& state,
    const std::string& file_name,
    const visualize::Property& visual_property
)
{
	const auto& [x_max, y_max] = xy_max_nodes(state.nodes);
    Cairo cairo(x_max, y_max, file_name);
    code_nodes(cairo, state, visual_property);
    code_tubes(cairo, state, visual_property);

}
