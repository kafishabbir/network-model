#ifndef GLOBAL_DECL_H
#define GLOBAL_DECL_H

#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

namespace decl
{
	const double pi = std::acos(-1);
	const int n_fluids = 2;
	namespace nps_latex_plot
	{
		namespace nps_file
		{
			const std::string figure_initial = "figure-";
			const std::string list_figures = "list-figures";
			const std::string template_main = "template/main.tex";
		}
		namespace nps_folder
		{
			const std::string results = "run/results/";
			const std::string figures = "figures/";
			const std::string output = "output";
		}
	}
}

#endif
