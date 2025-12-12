#include "generator/ic.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

const std::string flow_plot_output = "flow/figcode.tex";
const std::vector<std::string> colors{"cw", "cnw"};

std::string tikz_fill_rectangle(
	const std::string& color,
	const double x1,
	const double y1,
	const double x2,
	const double y2
)
{
	std::stringstream ss;
	ss << "\\fill" << "[" << color << "]";
	ss << "(" << x1 << ", " << y1 << ")";
	ss << " rectangle ";
	ss << "(" << x2 << ", " << y2 << ")" << ";";
	return ss.str();
}

std::string tikz_generate_rectangles(
	const std::vector<double>& v,
	const int fluid_first,
	const double radius,
	const double length
	)
{
	const int n = v.size();
	std::stringstream ss;
	for(int i = 1; i < n; ++ i)
	{
		const auto& color = colors[(i + fluid_first + 1) % 2];
		const double x1 = v[i - 1] * length;
		const double y1 = radius / 2;
		const double x2 = v[i] * length;
		const double y2 = - radius / 2;
		const auto& command_rectangle =
			tikz_fill_rectangle(color, x1, y1, x2, y2);

		ss << command_rectangle << "\n";
	}
	return ss.str();
}

std::string tikz_scope_shift_rotate(
	const double x,
	const double y,
	const double angle,
	const std::string& draw_rectangles_command
)
{
	std::stringstream ss;
	ss << "\\begin{scope}";
		ss << "[";
			ss << "shift={(" << x << ", " << y << ")}";
			ss << ", rotate=" << angle;
		ss << "]" << "\n";

		ss << draw_rectangles_command;
	ss << "\\end{scope}";

	return ss.str();
}


void draw_in_tikz(
	const std::vector<nst::Node>& v_nodes,
	const std::vector<nst::Tube>& v_tubes
)
{
	std::stringstream ss;

	const int n_tubes = v_tubes.size();
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = v_tubes[i];

		const auto& node_first = v_nodes[tube.id_node_first];
		const auto& node_second = v_nodes[tube.id_node_second];

		const double x1 = node_first.x;
		const double y1 = node_first.y;

		const double x2 = node_second.x;
		const double y2 = node_second.y;

		const double delta_x = x2 - x1;
		const double delta_y = y2 - y1;

		const double length = std::sqrt(delta_x * delta_x + delta_y * delta_y);
		std::string draw_rectangles_command = tikz_generate_rectangles(
			tube.mpos_long(),
			tube.fluid_first,
			tube.radius,
			length
		);

		const double angle = std::atan2(delta_y, delta_x) * 180 / std::acos(-1);

		const auto& scope_shifted_rotated_command =
			tikz_scope_shift_rotate(x1, y1, angle, draw_rectangles_command);

		ss << scope_shifted_rotated_command << "\n";
	}
	std::ofstream fout(flow_plot_output);
	std::cout <<  ss.str();
	fout << ss.str();
}

int main()
{
	const auto& [v_nodes, v_tubes] = generator::Ic::square_lattice(4, 6);

	const int n_nodes = v_nodes.size();
	const int n_tubes = v_tubes.size();

	std::cout << "Nodes data check" << std::endl;
	for(int i = 0; i < n_nodes; ++ i)
	{
		const auto& node = v_nodes[i];
		std::cout << "node_id=" << i << ", x=" << node.x << ", y=" << node.y << std::endl;
	}

	std::cout << "Tubes data check" << std::endl;
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = v_tubes[i];
		std::cout << "tubes_id=" << i << ", x=" << tube.id_node_first << ", y=" << tube.id_node_second << std::endl;
	}

	draw_in_tikz(v_nodes, v_tubes);
	return 0;
}
