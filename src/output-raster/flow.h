#ifndef VISUALIZE_RASTER_H
#define VISUALIZE_RASTER_H

#include "dst/system.h"
#include "output/property.h"
#include "output-raster/cairo.h"

namespace output_raster
{
	class Flow
	{
		static const std::vector<Cairo::Color> colors_v;

		static std::string mpos_horizontal_rectangles(
			const nst::Tube& tube,
			const std::vector<std::string>& colors
		);

		static void code_node(
			Cairo& cairo,
			const nst::Node& node,
			const output::Property& visual_property
		);

		static void code_tube(
			Cairo& cairo,
			const dst::State& state,
			int id_tube,
			const output::Property& visual_property
		);

		static void code_nodes(
			Cairo& cairo,
			const dst::State& state,
			const output::Property& visual_property
		);

		static void code_tubes(
			Cairo& cairo,
			const dst::State& state,
			const output::Property& visual_property
		);

		static std::pair<double, double> xy_max_nodes(
			const nst::Nodes& nodes
		);

		public:
		static void print_figure(
			const dst::State& state,
			const std::string& file_name,
			const output::Property& visual_property
		);
	};
}

#endif
