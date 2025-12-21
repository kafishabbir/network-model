#ifndef NST_TUBE_H
#define NST_TUBE_H

#include <vector>
namespace nst
{
	class Tube
	{
	public:
		int id_node_first;
		int id_node_second;
		double radius;
		double length;
		int fluid_first;
		std::vector<double> mpos; //meniscus positions
		std::vector<double> mpos_long() const;
		Tube();
	};
}
#endif
