#include "ic/geometry-flow.h"

ic::type_pair_nodes_tubes ic::GeometryFlow::network_geometry()
{
	return ic::GeometryBase::rectangular(16, 20);
}
