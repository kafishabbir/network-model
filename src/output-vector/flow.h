#ifndef OUTPUT_VECTOR_FLOW_H
#define OUTPUT_VECTOR_FLOW_H

namespace output_vector
{
    class Flow
    {

		std::vector<std::string> colors_str_v;


	public:


        static void save_latex_code_of_figure(
			const nst::State& state,
			const std::string& file_name,
			const output::Property& visual_property
		);

    };
}

#endif
