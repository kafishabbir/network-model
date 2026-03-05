#ifndef OUTPUT_VECTOR_DRAW_H
#define OUTPUT_VECTOR_DRAW_H

#include "output/property.h"
#include "dst/system.h"

namespace output_vector
{
	class Draw
	{
		
		static std::string mpos_horizontal_rectangles(
			const nst::Tube& tube,
			const output::Property& visual_property,
			const std::vector<std::string>& colors
		);
		
		static std::string draw_node(
			const nst::Node& node,
			const output::Property& visual_property,
			const std::vector<std::string>& colors
		);
		
		static std::string draw_tube(
			const nst::Tube& tube,
			const dst::State& state,
			const output::Property& visual_property,
			const std::vector<std::string>& colors
		);

	public:
		static std::string draw_tubes(
			const dst::State& state,
			const output::Property& visual_property,
			const std::vector<std::string>& colors
		);


		static std::string draw_nodes(
			const dst::State& state,
			const output::Property& visual_property,
			const std::vector<std::string>& colors
		);

	};
}

#endif
