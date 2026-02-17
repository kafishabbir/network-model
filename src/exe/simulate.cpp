#include "simulate/menu.h"
#include "ic/geometry-flow.h"
#include <iostream>

int main()
{
	//simulate::Menu::test_generate_and_plot();

	const auto [nodes, tubes] = ic::GeometryFlow::network_geometry(100, 100, 0, 0.5, 10, 1);

	double volume = 0;
	std::ofstream fout("input.txt");
	for(int i = 0; i < 100; ++ i)
	{
		for(int j = 0; j < 100; ++ j)
		{
			const int k = 100 * i + j;
			const auto& tube = tubes[k];
			fout << tube.radius << ' ';
			volume += tube.volume();
		}
		fout << '\n';
	}

	std::cout << "Total volume: " << volume;
	return 0;
}
