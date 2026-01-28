#include "visualize/draw-shapes.h"

std::string visualize::DrawShapes::mpos_horizontal_rectangles(
	const nst::Tube& tube,
	const std::vector<std::string>& colors
)
{
	const std::vector<double>& v = tube.mpos;
	const int fluid_first = tube.fluid_first;
	const double radius = tube.radius;

	const int n = v.size();
	std::stringstream ss;
	for(int i = 1; i < n; ++ i)
	{
		const auto& color = colors[(i + fluid_first + 1) % 2];
		const double x1 = v[i - 1];
		const double y1 = radius;
		const double x2 = v[i];
		const double y2 = - radius;
		const auto& tikz_str_single_fluid_block =
			visualize::TikzDraw::rectangle(color, x1, y1, x2, y2);

		ss << tikz_str_single_fluid_block << '\n';
	}
	return ss.str();
}


std::string visualize::DrawShapes::circle(
	const double x,
	const double y,
	const double radius
)
{
	std::stringstream ss;
	ss << "\\draw" << "(" << x << ", " << y << ") " << "circle" << "(" << radius << ")" << ";";
	return ss.str();
}

std::string visualize::DrawShapes::node(
	const double x,
	const double y,
	const std::string& node_text
)
{
	std::stringstream ss;
	ss << "\\node" << " at " << "(" << x << ", " << y << ") " << "{" << node_text << "}" << ";";
	return ss.str();
}
