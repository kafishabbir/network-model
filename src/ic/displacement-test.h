#ifndef IC_DISPLACEMENT_TEST_H
#define IC_DISPLACEMENT_TEST_H

#include "global/dst.h"
#include <utility>

namespace ic
{
	class DisplacementTest
	{
		static dst::Tubes generate_tubes_rectangular(
			const int n_rows_tube,
			const int n_cols_tube
		);

		static dst::Nodes generate_nodes_rectangular(
			const int n_rows_tube,
			const int n_cols_tube
		);

		static nst::State generate_rectangular(
			const int n_rows_tube,
			const int n_cols_tube
		);
	public:


		static nst::State generate_rectangular();
	};

}

#endif
