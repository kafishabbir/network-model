#ifndef VISUALIZE_DRAW_SHAPES_H
#define VISUALIZE_DRAW_SHAPES_H

#include "nst/tube.h"
#include "visualize/tikz-draw.h"
#include <iomanip>

namespace visualize
{
	class Draw
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

		static std::string num(double val);

		static std::string arrow(
			const double x_begin,
			const double x_end,
			const double y
		);
	};

}

#endif
