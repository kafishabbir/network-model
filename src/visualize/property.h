#ifndef VISUALIZE_PROPERTY_H
#define VISUALIZE_PROPERTY_H

#include "global/decl.h"

namespace visualize
{
    class Property
    {
        public:

		std::vector<std::string> colors_str_v;

        // Tube visualization properties
        double tube_radius_min;
        double tube_radius_max;
        double largest_angle_tube_project_on_node;

        // Node visualization properties
        bool draw_node_perimeter;

        // Label visibility properties
        bool label_node_id;
        bool label_node_pressure;
        bool label_tube_id;
        bool label_tube_radius;
        bool label_tube_length;
        bool label_tube_flow_rate;

		Property();
    };
}

#endif
