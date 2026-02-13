#ifndef VISUALIZE_FLOW_VERIFICATION_LABEL_H
#define VISUALIZE_FLOW_VERIFICATION_LABEL_H

#include "visualize/draw.h"

namespace visualize
{
    class FlowVerificationLabel
    {
		static std::string node_details(const nst::Node& node);

		static std::string label_tube_above(const nst::Tube& tube, const visualize::Property& visual_property);
		static std::string code_node_label(const nst::Node& node, const int id_node, const visualize::Property& visual_property);
		static std::string code_tube(const nst::State& state, const int id_tube, const visualize::Property& visual_property);

        public:

        static std::string code_nodes_labels(const nst::State& state, const visualize::Property& visual_property);
        static std::string code_tubes_labels(const nst::State& state, const visualize::Property& visual_property);
    };
}

#endif
