#include "visualize/flow.h"

const std::vector<std::string> visualize::Flow::COLORS{"cw", "cnw"};

// The minumum and maximum radius in proportion to the minimum tube length
const double visualize::Flow::R_MIN = 0.02;
const double visualize::Flow::R_MAX = 0.1;
/*
 * This controls the node size
 * Thick tube && low angle => huge node
 */
const double visualize::Flow::LARGEST_ANGLE_A_TUBE_CAN_PROJECT_ON_NODE = std::acos(-1) / 2.0;

const bool visualize::Flow::PLOT_FEATURE_ACTIVE_DISPLAY_NODE = true;
const bool visualize::Flow::PLOT_FEATURE_LABEL_NODE_NUMBER = true;
const bool visualize::Flow::PLOT_FEATURE_LABEL_TUBE_NUMBER = true;
const bool visualize::Flow::PLOT_FEATURE_LABEL_TUBE_FLOW_RATE = true;


std::string flow_rate_information(const nst::Tube& tube, const nst::Tube& tube_visual)
{
	const int i = tube.id_node_first;
	const int j = tube.id_node_second;
	const double r = tube.radius;
	const double l = tube.length;
	const double q = tube.flow_rate;
	std::stringstream ss, ss_q, ss_rl;
	ss_q << "$" << "q_{" << i << j << "}=" << q << "$";
	ss_rl << "$r=" << r << "$, $l=" << l << "$";

	const double rv = tube_visual.radius;
	const double lv = tube_visual.length;

	double arrow_begin = lv/8;
	double arrow_end = lv*3/8;
	if(q<0)
	{
		arrow_begin = lv*7/8;
		arrow_end = lv*5/8;
	}
	ss << "\\draw[->] (" << arrow_begin << ", " << -1.75 * rv << ") -- (" << arrow_end << ", " << -1.75 * rv << ");";

	ss << visualize::DrawShapes::node(lv / 2, -2 * rv, ss_q.str()) << "\n";
	ss << visualize::DrawShapes::node(lv / 2, 2 * rv, ss_rl.str()) << "\n";
	return ss.str();
}

Nodes visualize::Flow::scale_coordinates_to_unit_scale(Nodes v)
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

double visualize::Flow::calculate_tube_displacement_due_to_node(
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

Tubes visualize::Flow::scale_mpos_long(Tubes tubes, const Nodes& nodes)
{
	for(auto& tube: tubes)
	{
		const auto& node_first = nodes[tube.id_node_first];
		const auto& node_second = nodes[tube.id_node_second];
		const double p1 = calculate_tube_displacement_due_to_node(node_first.radius, tube.radius);
		const double p2 = calculate_tube_displacement_due_to_node(node_second.radius, tube.radius);
		const double length_effective = tube.length - p1 - p2;

		tube.mpos = tube.mpos_long();
		for(auto& pos: tube.mpos)
		{
			pos *= length_effective;
			pos += p1;
		}
	}

	return tubes;
}

Tubes visualize::Flow::scale_set_tube_length_to_visual_length(Tubes tubes, const Nodes& nodes)
{
	for(auto& tube: tubes)
	{
		const auto& node_first = nodes[tube.id_node_first];
		const auto& node_second = nodes[tube.id_node_second];
		tube.length = node_first.distance(node_second);
	}

	return tubes;
}

std::pair<double, double> visualize::Flow::radius_min_max(const Tubes& tubes)
{
	double r_min = tubes.front().radius;
	double r_max = tubes.front().radius;

	for(const auto& tube: tubes)
	{
		r_min = std::min(tube.radius, r_min);
		r_max = std::max(tube.radius, r_max);
	}

	return {r_min, r_max};
}

double visualize::Flow::length_min(const Tubes& tubes)
{
	double l_min = tubes.front().radius;

	for(const auto& tube: tubes)
	{
		l_min = std::min(tube.length, l_min);
	}

	return l_min;
}

Tubes visualize::Flow::scale_radius(Tubes tubes)
{
	const auto [r_min, r_max] = radius_min_max(tubes);

	const double delta_r = r_max - r_min;
	const bool slope_not_possible = ((delta_r / r_max) <= 0.01);
	const double min_length = length_min(tubes);

	if(slope_not_possible)
	{
		for(auto& tube: tubes)
		{
			tube.radius = min_length * (R_MIN + R_MAX) / 2;
		}
		return tubes;
	}

	const double DELTA_R = R_MAX - R_MIN;

	for(auto& tube: tubes)
	{
		tube.radius = min_length * (
			R_MIN + DELTA_R / delta_r * (tube.radius - r_min)
		);
	}

	return tubes;
}

Nodes visualize::Flow::assign_radius_to_each_node(
	Nodes nodes,
	const Tubes& tubes
)
{
	for(const auto& tube: tubes)
	{
		auto& node_first = nodes[tube.id_node_first];
		auto& node_second = nodes[tube.id_node_second];

		node_first.radii_of_tubes_attached_to_this_node.push_back(tube.radius);
		node_second.radii_of_tubes_attached_to_this_node.push_back(tube.radius);
	}

	for(auto& node: nodes)
	{
		const auto& v = node.radii_of_tubes_attached_to_this_node;
		const auto max_radius = *max_element(v.cbegin(), v.cend());
		const auto theta = LARGEST_ANGLE_A_TUBE_CAN_PROJECT_ON_NODE;
		node.radius = max_radius / std::sin(theta / 2.0);
	}

	return nodes;
}

std::string visualize::Flow::tikz_string_single_plot(
	const State& state
)
{
	auto nodes = state.nodes;
	auto tubes = state.tubes;

	nodes = scale_coordinates_to_unit_scale(state.nodes);

	tubes = scale_set_tube_length_to_visual_length(tubes, nodes);
	tubes = scale_radius(tubes);

	if(PLOT_FEATURE_ACTIVE_DISPLAY_NODE)
	{
		nodes = assign_radius_to_each_node(nodes, tubes);
	}
	tubes = scale_mpos_long(tubes, nodes);


	std::stringstream ss;

	const int n_tubes = tubes.size();
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = tubes[i];
		const auto& node_first = nodes[tube.id_node_first];
		const auto& node_second = nodes[tube.id_node_second];

		auto command_horizontal_tube =
			visualize::DrawShapes::mpos_horizontal_rectangles(tube, COLORS);

		if(PLOT_FEATURE_LABEL_TUBE_FLOW_RATE)
		{
			command_horizontal_tube += flow_rate_information(state.tubes[i], tube);
		}

		const auto& command_tube =
			visualize::TikzDraw::scope(
				node_first.x,
				node_first.y,
				node_first.relative_angle(node_second),
				command_horizontal_tube
			);

		ss << command_tube << '\n';
	}

	if(PLOT_FEATURE_ACTIVE_DISPLAY_NODE)
	{
		for(const auto& node: nodes)
		{
			double radius = node.radius;
			double x = node.x;
			double y = node.y;

			ss << visualize::DrawShapes::circle(x, y, radius) << "\n";
		}
	}

	if(PLOT_FEATURE_LABEL_NODE_NUMBER)
	{
		const int n_nodes = nodes.size();
		for(int i = 0; i < n_nodes; ++ i)
		{
			const auto& node = nodes[i];
			double x = node.x;
			double y = node.y;

			std::stringstream ss_node;
			ss_node << "$\\nu_{" << i << "}$";
			ss << visualize::DrawShapes::node(x, y, ss_node.str()) << "\n";

			std::stringstream ss_pressure;
			ss_pressure << "$p=" << node.pressure << "$";
			ss << visualize::DrawShapes::node(x, y  + 1.2*node.radius, ss_pressure.str()) << "\n";
		}
	}

	if(PLOT_FEATURE_LABEL_TUBE_NUMBER)
	{
		const int n_tubes = tubes.size();
		for(int i = 0; i < n_tubes; ++ i)
		{
			const auto& tube = tubes[i];
			const auto& node_first = nodes[tube.id_node_first];
			const auto& node_second = nodes[tube.id_node_second];

			const double x = (node_first.x + node_second.x) / 2;
			const double y = (node_first.y + node_second.y) / 2;
			ss << visualize::DrawShapes::node(x, y, std::to_string(i)) << "\n";
		}
	}

	return visualize::LatexBasicCommands::scope("tikzpicture", ss.str(), "scale=\\imagewidthscale");
}

void visualize::Flow::mpos_multiple_plots_in_1_pdf(
	const States& states
)
{
	// It takes in a nodes and tube data
	// Each plot has its own node and tube data

	// n_plots: number of plots
	const int n_plots = states.size();

	// the file structure of the plots are like this
	// run/flow/main.tex
	// run/flow/listfigures.tex
	// run/flow/figures/fig-xx.tex
	// fout_list_figures: file output to listfigures.tex
	// this lists all the plots and the captions
	// each of these includes the figures/fig-1xx.tex
	std::ofstream fout_list_figures(visualize::FlowFileOut::file_list_figures());
	for(int i = 0; i < n_plots; ++ i)
	{
		const auto& state = states[i];

		// Write the tikz code of the figure to run/flow/figures/fig-1xx.tex
		visualize::FlowFileOut file_figure(i);
		std::ofstream fout_figure(file_figure.path());
		fout_figure << tikz_string_single_plot(state);

		// Write begin{figure} end{figure} to run/flow/listfigures.tex
		std::stringstream ss_caption;
		ss_caption << "This figure, " << file_figure.file_name();

		const auto& scope_beign_end_figure =
			visualize::LatexBasicCommands::begin_end_figure_with_captions(
				file_figure.path_for_latex_input(),
				ss_caption.str()
			);

		fout_list_figures << scope_beign_end_figure << '\n';
	}
}
