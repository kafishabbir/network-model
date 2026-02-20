#ifndef VISUALIZE_RASTER_H
#define VISUALIZE_RASTER_H

#include "global/dst.h"
#include "visualize/property.h"

#include <cairo/cairo.h>
#include <sstream>
#include <functional>
#include <cmath>


namespace nst
{
    struct State;
    struct Tube;
    struct Node;
}

namespace visualize
{
    struct Property;

    class Raster
    {
        static void circle(
            cairo_t* cr,
            double x,
            double y,
            double radius
        );

        static void rectangle(
            cairo_t* cr,
            double x1,
            double y1,
            double x2,
            double y2
        );

        static void scope_shift_and_rotate(
            cairo_t* cr,
            double shift_to_x,
            double shift_to_y,
            double rotate_angle,
            std::function<void(cairo_t*)> draw_function
        );

        static std::string mpos_horizontal_rectangles(
            const nst::Tube& tube,
            const std::vector<std::string>& colors
        );

        static void code_node(
            cairo_t* cr,
            const nst::Node& node,
            const visualize::Property& visual_property
        );

        static void code_tube(
            cairo_t* cr,
            const nst::State& state,
            int id_tube,
            const visualize::Property& visual_property
        );

        static void code_nodes(
            cairo_t* cr,
            const nst::State& state,
            const visualize::Property& visual_property
        );

        static void code_tubes(
            cairo_t* cr,
            const nst::State& state,
            const visualize::Property& visual_property
        );

        public:
        static void flow(
            const nst::State& state,
            const std::string& file_name,
            const visualize::Property& visual_property
        );
    };
}

#endif
