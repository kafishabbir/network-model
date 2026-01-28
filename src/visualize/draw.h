#ifndef VISUALIZE_DRAW_SHAPES_H
#define VISUALIZE_DRAW_SHAPES_H

#include "nst/tube.h"
#include "visualize/tikz-draw.h"

namespace visualize
{
	class DrawShapes
	{

	public:
		static std::string mpos_horizontal_rectangles(
			const nst::Tube& tube,
			const std::vector<std::string>& colors
		);

		static std::string circle(
			const double x,
			const double y,
			const double radius
		);

		static std::string node(
			const double x,
			const double y,
			const std::string& node_text
		);
	};

}

#endif
