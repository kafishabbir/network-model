#include "visualize/raster.h"

void visualize::Raster::circle(
    cairo_t* cr,
    double x,
    double y,
    double radius
)
{
    cairo_arc(cr, x, y, radius, 0, 2 * M_PI);
    cairo_stroke(cr);
}

void visualize::Raster::rectangle(
    cairo_t* cr,
    double x1,
    double y1,
    double x2,
    double y2
)
{
    double width = x2 - x1;
    double height = y2 - y1;
    cairo_rectangle(cr, x1, y1, width, height);
    cairo_fill(cr);
}

void visualize::Raster::scope_shift_and_rotate(
    cairo_t* cr,
    double shift_to_x,
    double shift_to_y,
    double rotate_angle,
    std::function<void(cairo_t*)> draw_function
)
{
    cairo_save(cr);
    cairo_translate(cr, shift_to_x, shift_to_y);
    cairo_rotate(cr, rotate_angle * M_PI / 180.0);
    draw_function(cr);
    cairo_restore(cr);
}

std::string visualize::Raster::mpos_horizontal_rectangles(
    const nst::Tube& tube,
    const std::vector<std::string>& colors
)
{
    const std::vector<double>& v = tube.visual.mpos;
    int id_fluid_first = tube.id_fluid_first;
    double radius = tube.visual.radius;

    int n = v.size();
    std::stringstream ss;
    for(int i = 1; i < n; ++ i)
    {
        const auto& color = colors[(i + id_fluid_first + 1) % 2];
        double x1 = v[i - 1];
        double y1 = radius;
        double x2 = v[i];
        double y2 = -radius;

        ss << "rectangle " << color << " " << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
    }
    return ss.str();
}

void visualize::Raster::code_node(
    cairo_t* cr,
    const nst::Node& node,
    const visualize::Property& visual_property
)
{
    double x = node.visual.x;
    double y = node.visual.y;
    double radius = node.visual.radius;

    if(visual_property.draw_node_perimeter)
    {
        cairo_set_source_rgb(cr, 0, 0, 0);
        circle(cr, x, y, radius);
    }
}

void visualize::Raster::code_tube(
    cairo_t* cr,
    const nst::State& state,
    int id_tube,
    const visualize::Property& visual_property
)
{
    const auto& tube = state.tubes[id_tube];
    const auto& node_first = state.nodes[tube.id_node_first];
    const auto& node_second = state.nodes[tube.id_node_second];

    std::string rect_cmds = mpos_horizontal_rectangles(tube, visual_property.colors_str_v);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_rectangle(cr, node_first.visual.x*100, node_first.visual.y*100, 20, 20);
    cairo_fill(cr);

}

void visualize::Raster::code_nodes(
    cairo_t* cr,
    const nst::State& state,
    const visualize::Property& visual_property
)
{
    const auto& nodes = state.nodes;
    int n_nodes = nodes.size();
    for(int i = 0; i < n_nodes; ++ i)
    {
        code_node(cr, nodes[i], visual_property);
    }
}

void visualize::Raster::code_tubes(
    cairo_t* cr,
    const nst::State& state,
    const visualize::Property& visual_property
)
{
    const auto& tubes = state.tubes;
    int n_tubes = tubes.size();
    for(int i = 0; i < n_tubes; ++ i)
    {
        code_tube(cr, state, i, visual_property);
    }
}

void visualize::Raster::flow(
    const nst::State& state,
    const std::string& file_name,
    const visualize::Property& visual_property
)
{
    double width = 800;
    double height = 600;

    std::string full_path = "run/results/flow/images/" + file_name + ".png";

    cairo_surface_t* surface = cairo_image_surface_create(
        CAIRO_FORMAT_ARGB32, width, height
    );
    cairo_t* cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    cairo_set_source_rgb(cr, 0, 0, 0);
    code_nodes(cr, state, visual_property);
    code_tubes(cr, state, visual_property);

    cairo_surface_write_to_png(surface, full_path.c_str());

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
