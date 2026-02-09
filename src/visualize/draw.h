#ifndef VISUALIZE_DRAW_H
#define VISUALIZE_DRAW_H

#include "nst/tube.h"
#include <iomanip>

namespace visualize
{
	class Draw
	{
		static std::string rectangle(
			const std::string& color,
			const double x1,
			const double y1,
			const double x2,
			const double y2
		);

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

		static std::string num(const double val);

		static std::string arrow(
			const double x_begin,
			const double x_end,
			const double y
		);
	};

}

#endif
