#include "output-vector/flow.h"
#include "output-vector/label-tube.h"
#include "output-vector/label-node.h"
#include "output-vector/draw.h"
#include "output/latex.h"
#include <fstream>

const std::vector<std::string> output_vector::Flow::colors_str_v{"cw", "cnw", "cmx"};


void output_vector::Flow::save_latex_code_of_figure(
	const dst::State& state,
	const std::string& file_name,
	const output::Property& visual_property
)
{
	std::stringstream ss;

	ss << Draw::draw_tubes(state, visual_property, colors_str_v) << '\n';
	ss << Draw::draw_nodes(state, visual_property, colors_str_v) << '\n';

	ss << LabelNode::basic(state) << '\n';
	if(visual_property.vector_image_label_node_detail)
	{
		ss << LabelNode::details(state) << '\n';
	}

	ss << LabelTube::basic(state) << '\n';
	if(visual_property.vector_image_label_tube_detail)
	{
		ss << LabelTube::details(state) << '\n';
	}

	std::ofstream fout(file_name + ".tex");
	fout << output::Latex::scope_tikzpicture(ss.str());
}
