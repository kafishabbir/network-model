#ifndef VISUALIZE_RASTER_H
#define VISUALIZE_RASTER_H

#include "global/dst.h"
#include "visualize/property.h"
#include "visualize/cairo.h"

namespace visualize
{
    struct Property;

    class Raster
    {
		static const std::vector<Cairo::Color> colors_v;

        static std::string mpos_horizontal_rectangles(
            const nst::Tube& tube,
            const std::vector<std::string>& colors
        );

        static void code_node(
            Cairo& cairo,
            const nst::Node& node,
            const visualize::Property& visual_property
        );

        static void code_tube(
            Cairo& cairo,
            const nst::State& state,
            int id_tube,
            const visualize::Property& visual_property
        );

        static void code_nodes(
            Cairo& cairo,
            const nst::State& state,
            const visualize::Property& visual_property
        );

        static void code_tubes(
            Cairo& cairo,
            const nst::State& state,
            const visualize::Property& visual_property
        );

		static std::pair<double, double> xy_max_nodes(
			const dst::Nodes& nodes
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
