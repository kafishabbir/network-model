#ifndef VISUALIZE_TIKZ_DRAW
#define VISUALIZE_TIKZ_DRAW

#include "visualize/latex-basic-commands.h"

namespace visualize
{
	class TikzDraw
	{

	public:
		static std::string scope(
			const double shift_to_x,
			const double shift_to_y,
			const double rotate_angle,
			const std::string& draw_commands_to_scope
		);

		static std::string rectangle(
			const std::string& color,
			const double x1,
			const double y1,
			const double x2,
			const double y2
		);
	};
}


#endif
