#include "plot/flow.h"

const std::vector<std::string> plot::Flow::COLORS{"cw", "cnw"};

const double plot::Flow::R_MIN = 0.1;
const double plot::Flow::R_MAX = 0.3;
const double plot::Flow::LARGEST_ANGLE_A_TUBE_CAN_PROJECT_ON_NODE = std::acos(-1) / 2;
const bool plot::Flow::PLOT_FEATURE_ACTIVE_DISPLAY_NODE = true;

std::string plot::Flow::tikz_string_rectangles_mpos_horizontal(const nst::Tube& tube)
{
	const std::vector<double>& v = tube.mpos;
	const int fluid_first = tube.fluid_first;
	const double radius = tube.radius;

	const int n = v.size();
	std::stringstream ss;
	for(int i = 1; i < n; ++ i)
	{
		const auto& color = COLORS[(i + fluid_first + 1) % 2];
		const double x1 = v[i - 1];
		const double y1 = radius / 2;
		const double x2 = v[i];
		const double y2 = - radius / 2;
		const auto& command_rectangle =
			plot::LatexCode::tikz_string_one_filled_rectangle(color, x1, y1, x2, y2);

		ss << command_rectangle << '\n';
	}
	return ss.str();
}


Nodes plot::Flow::scale_coordinates_to_unit_scale(Nodes v)
{
	double min = v.front().x;
	double max = v.front().x;

	for(const auto& node: v)
	{
		min = std::min(node.x, min);
		max = std::max(node.x, max);
	}

	const double length = max - min;

	for(auto& node: v)
	{
		node.x /= length;
		node.y /= length;
	}

	return v;
}

double plot::Flow::calculate_tube_displacement_due_to_node(
	const double r_node,
	const double r_tube
)
{
	if(!PLOT_FEATURE_ACTIVE_DISPLAY_NODE)
	{
		return 0;
	}

	return std::sqrt(r_node * r_node - r_tube * r_tube);
}

Tubes plot::Flow::scale_mpos_long(Tubes v_tubes, const Nodes& v_nodes)
{
	for(auto& tube: v_tubes)
	{
		const auto& node_first = v_nodes[tube.id_node_first];
		const auto& node_second = v_nodes[tube.id_node_second];
		const double p1 = calculate_tube_displacement_due_to_node(node_first.radius, tube.radius);
		const double p2 = calculate_tube_displacement_due_to_node(node_second.radius, tube.radius);
		const double length_effective = tube.length - p1 - p2;

		tube.mpos = tube.mpos_long();
		for(auto& pos: tube.mpos)
		{
			pos *= length_effective + p1;
		}
	}

	return v_tubes;
}

Tubes plot::Flow::scale_set_tube_length_to_visual_length(Tubes v_tubes, const Nodes& v_nodes)
{
	for(auto& tube: v_tubes)
	{
		const auto& node_first = v_nodes[tube.id_node_first];
		const auto& node_second = v_nodes[tube.id_node_second];
		tube.length = node_first.distance(node_second);
	}

	return v_tubes;
}


std::pair<double, double> plot::Flow::radius_min_max(const Tubes& v_tubes)
{
	double r_min = v_tubes.front().radius;
	double r_max = v_tubes.front().radius;

	for(const auto& tube: v_tubes)
	{
		r_min = std::min(tube.radius, r_min);
		r_max = std::max(tube.radius, r_max);
	}

	return {r_min, r_max};
}

double plot::Flow::length_min(const Tubes& v_tubes)
{
	double l_min = v_tubes.front().radius;

	for(const auto& tube: v_tubes)
	{
		l_min = std::min(tube.length, l_min);
	}

	return l_min;
}

Tubes plot::Flow::scale_radius(Tubes v_tubes)
{
	const auto [r_min, r_max] = radius_min_max(v_tubes);

	const double delta_r = r_max - r_min;
	const bool slope_not_possible = ((delta_r / r_max) <= 0.01);

	const double DELTA_R = R_MAX - R_MIN;

	const double min_length = length_min(v_tubes);
	for(auto& tube: v_tubes)
	{
		if(slope_not_possible)
		{
			tube.radius = (R_MIN + R_MAX) / 2;
		}
		else
		{
			tube.radius =
				R_MIN + (tube.radius - r_min) / delta_r * DELTA_R;
		}
		tube.radius *= min_length;
	}

	return v_tubes;
}

Nodes plot::Flow::assign_radius_to_each_node(
	Nodes v_nodes,
	const Tubes& v_tubes
)
{
	for(const auto& tube: v_tubes)
	{
		auto& node_first = v_nodes[tube.id_node_first];
		auto& node_second = v_nodes[tube.id_node_second];

		node_first.radii_of_tubes_attached_to_this_node.push_back(tube.radius);
		node_second.radii_of_tubes_attached_to_this_node.push_back(tube.radius);
	}

	for(auto& node: v_nodes)
	{
		const auto& v = node.radii_of_tubes_attached_to_this_node;
		const auto max_radius = *max_element(v.cbegin(), v.cend());
		const auto theta = LARGEST_ANGLE_A_TUBE_CAN_PROJECT_ON_NODE;
		node.radius = max_radius / std::sin(theta / 2);
	}

	return v_nodes;
}

std::string plot::Flow::tikz_string_single_plot(
	Nodes v_nodes,
	Tubes v_tubes
)
{
	v_nodes= scale_coordinates_to_unit_scale(v_nodes);

	v_tubes = scale_set_tube_length_to_visual_length(v_tubes, v_nodes);
	v_tubes = scale_radius(v_tubes);

	if(PLOT_FEATURE_ACTIVE_DISPLAY_NODE)
	{
		v_nodes = assign_radius_to_each_node(v_nodes, v_tubes);
	}
	v_tubes = scale_mpos_long(v_tubes, v_nodes);


	std::stringstream ss;

	for(const auto& tube: v_tubes)
	{
		const auto& node_first = v_nodes[tube.id_node_first];
		const auto& node_second = v_nodes[tube.id_node_second];

		const auto& command_horizontal_tube =
			tikz_string_rectangles_mpos_horizontal(tube);

		const auto& command_tube =
			plot::LatexCode::tikz_scope_shift_rotate(
				node_first.x,
				node_first.y,
				node_first.relative_angle(node_second),
				command_horizontal_tube
			);

		ss << command_tube << '\n';
	}

	return plot::LatexCode::scope("tikzpicture", ss.str(), "scale=\\imagewidthscale");
}


void plot::Flow::mpos_multiple_plots_in_1_pdf(
	const std::vector<std::pair<Nodes, Tubes>>& v_plots
)
{
	// It takes in a nodes and tube data
	// Each plot has its own node and tube data

	// n_plots: number of plots
	const int n_plots = v_plots.size();

	// the file structure of the plots are like this
	// run/flow/main.tex
	// run/flow/listfigures.tex
	// run/flow/figures/fig-xx.tex
	// fout_list_figures: file output to listfigures.tex
	// this lists all the plots and the captions
	// each of these includes the figures/fig-1xx.tex
	std::ofstream fout_list_figures(plot::FilePath::file_list_figures());
	for(int i = 0; i < n_plots; ++ i)
	{
		const auto& [v_nodes, v_tubes] = v_plots[i];

		plot::FilePath file_path_figure(i);

		// Write begin{figure} end{figure} to run/flow/listfigures.tex
		std::stringstream ss_caption;
		ss_caption << "This figure, " << file_path_figure.file_name_without_tex();
		const auto& scope_beign_end_figure = plot::LatexCode::scope_figure(
				file_path_figure.path_for_latex(),
				ss_caption.str()
			);
		fout_list_figures << scope_beign_end_figure << '\n';

		// Write the tikz code of the figure to run/flow/figures/fig-1xx.tex
		const auto& path_plot = file_path_figure.path_for_io_and_exe();
		std::ofstream fout_figure(path_plot);
		fout_figure << tikz_string_single_plot(v_nodes, v_tubes);
	}
}


