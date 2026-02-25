#ifndef OUTPUT_VECTOR_TIKZ_H
#define OUTPUT_VECTOR_TIKZ_H

#include <string>
#include "utility/str.h"
namespace output_vector
{
    class Tikz
    {

		static inline constexpr auto d = utility::Str::general;
		static inline constexpr auto s = utility::Str::scientific;
		
	public:
		static std::string rectangle(
			const std::string& color,
			const double x1,
			const double y1,
			const double x2,
			const double y2
		);

		static std::string circle(
			const double x,
			const double y,
			const double radius, 
			const std::string& color
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

		static std::string node_long(
			const double x,
			const double y,
			const std::string& node_text
		);

		static std::string arrow(
			const double x_begin,
			const double x_end,
			const double y
		);

		/*
		begin{scope}[shift={(x, y)}, rotate=angle]
			draw_commands_to_scope
		end{scope}
		*/
		static std::string scope_shift_and_rotate(
			const double shift_to_x,
			const double shift_to_y,
			const double rotate_angle,
			const std::string& draw_commands_to_scope
		);
    };
}

#endif
