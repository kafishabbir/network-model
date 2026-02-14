#ifndef VISUALIZE_PROPERTY_H
#define VISUALIZE_PROPERTY_H

#include "global/dst.h"

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
        bool label_id_node;
        bool label_node_pressure;
        bool label_id_tube;
        bool label_tube_radius;
        bool label_tube_length;
        bool label_tube_flow_rate;
        bool label_tube_direction;
        bool label_capillary_pressure;
        bool label_tube_velocity;
        bool label_tube_time;

		bool label_node_details;
		bool label_tube_details;
		Property();
    };
}

#endif
