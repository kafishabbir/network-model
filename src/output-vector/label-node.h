#ifndef OUTPUT_VECTOR_LABEL_NODE_H
#define OUTPUT_VECTOR_LABEL_NODE_H

#include "global/dst.h"
#include "output/property.h"
#include "utility/str.h"

namespace output_vector
{
	class LabelNode
	{
		static inline constexpr auto s = utility::Str::scientific;
		static inline constexpr auto v = utility::Str::vector;
		
		static std::string label_node_details(const nst::Node& node);
		static std::string label_node_basic(const nst::Node& node, const int id_node);

	public:
		static std::string basic(const nst::State& state);
		static std::string details(const nst::State& state);
	};
}

#endif

