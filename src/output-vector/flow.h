#ifndef OUTPUT_VECTOR_FLOW_H
#define OUTPUT_VECTOR_FLOW_H

#include "dst/system.h"
#include "output/property.h"

namespace output_vector
{
    class Flow
    {

		static const std::vector<std::string> colors_str_v;
	public:
        static void save_latex_code_of_figure(
			const dst::System& state,
			const std::string& file_name,
			const output::Property& visual_property
		);

    };
}

#endif
