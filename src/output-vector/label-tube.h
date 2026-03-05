#ifndef OUTPUT_VECTOR_LABEL_TUBE_H
#define OUTPUT_VECTOR_LABEL_TUBE_H

#include "dst/system.h"
#include "utility/str.h"

namespace output_vector
{
	class LabelTube
	{
		static inline constexpr auto s = utility::Str::scientific;
		static inline constexpr auto v = utility::Str::vector_double;
		
		static std::pair<int, int> id_node_flow_direction(
			const int id_node_first, 
			const int id_node_second, 
			const double flow_rate
		);
		
		static std::pair<double, double> pos_arrow_flow_direction(
			const double visual_length, 
			const double flow_rate
		);
		
		static std::string label_id_tube(const int id_tube);
		
		static std::string label_ij_flow_rate(
			const int i, 
			const int j, 
			const double flow_rate
		);
		
		static std::string label_tube_basic(
			const nst::Tube& tube, 
			const int id_tube,
			const dst::State& state
		);
		
		static std::string label_tube_details(
			const nst::Tube& tube,
			const dst::State& state
		);

	public:
		static std::string basic(const dst::State& state);
		static std::string details(const dst::State& state);
	};
}

#endif
