#ifndef VISUALIZE_PROPERTY_H
#define VISUALIZE_PROPERTY_H

#include "dst/system.h"

namespace output
{
	class Property
	{
		
		
		public:
		// Tube visualization properties
		double tube_radius_min;
		double tube_radius_max;
		double largest_angle_tube_project_on_node;

		// Node visualization properties
		bool vector_image_draw_shape_perimeter;
		bool vector_image_label_node_detail;
		bool vector_image_label_tube_detail;

		Property();
	};
}

#endif
