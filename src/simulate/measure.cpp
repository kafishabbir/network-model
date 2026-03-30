#include "simulate/measure.h"
#include <algorithm>
#include <cmath>

nst::Tank simulate::Measure::tube_inventory(const nst::Tube& tube)
{
	const auto& v = tube.mpos_long();
	const int n = v.size();
	const double vol = tube.volume();
	nst::Tank tank;
	for(int i = 1; i < n; ++ i)
	{
		const int id_fluid = (tube.id_fluid_first + 1 + i) % 2;
		const double l = v[i] - v[i - 1];
		tank.add_fluid(vol * l, id_fluid);
	}

	return tank;
}

nst::Tank simulate::Measure::fluid_in_system(const dst::System& system)
{
	nst::Tank tank;
	for(const auto& tube: system.state.tubes)
	{
		tank.add_fluid(tube_inventory(tube));
	}

	return tank;
}

std::vector<std::pair<double, double>> simulate::Measure::generate_saturation_vs_x(
	const dst::System& system
)
{
	std::vector<nst::Tank> tanks(system.parameter.geometry.n_tube_cols);
	
	const int n_tanks = tanks.size();
	
	for(const auto& tube: system.state.tubes)
	{
		const double x1 = system.state.nodes[tube.id_node_first].x;
		const double x2 = system.state.nodes[tube.id_node_second].x;
		const double x = (x1 + x2) / 2;
		
		const int index = std::floor(x * n_tanks);
		tanks.at(index).add_fluid(simulate::Measure::tube_inventory(tube));
	}
	
	std::vector<std::pair<double, double>> v;
	
	for(int i = 0; i < n_tanks; ++ i)
	{
		const double x = (0.5 + i) / n_tanks;
		v.push_back({x, tanks[i].saturation()});
	}
	
	return v;
}




std::vector<dst::State::Calculated::SquaredData> simulate::Measure::generate_squared_data(
	const dst::System& system
)
{
	const int n_row_division = 10;
	const int n_col_division = 10;
	std::vector<std::vector<nst::Tank>> tanks(n_row_division, std::vector<nst::Tank>(n_col_division));
	
	for(const auto& tube: system.state.tubes)
	{
		const double x1 = system.state.nodes[tube.id_node_first].x;
		const double x2 = system.state.nodes[tube.id_node_second].x;
		const double x = (x1 + x2) / 2;
		
		
		const double y1 = system.state.nodes[tube.id_node_first].y;
		const double y2 = system.state.nodes[tube.id_node_second].y;
		const double y = (y1 + y2) / 2;
		
		
		const int index_x = std::floor(x * n_row_division);
		const int index_y = std::floor(y * n_col_division);
		
		auto& tank_row = tanks.at(index_x);
		auto& tank = tank_row.at(index_y);
		tank.add_fluid(simulate::Measure::tube_inventory(tube));
	}
	
	
	
	 std::vector<dst::State::Calculated::SquaredData> squared_data_v;
	
	
	for(int row_i = 0; row_i < n_row_division; ++ row_i)
	{
		for(int col_i = 0; col_i < n_col_division; ++ col_i)
		{
			const auto& tank = tanks[row_i][col_i];
			
			dst::State::Calculated::SquaredData squared_data;
			
			squared_data.x_begin = row_i;
			squared_data.x_end = row_i + 1;
			squared_data.y_begin = col_i;
			squared_data.y_end = col_i + 1;
			
			squared_data.x_begin /= n_row_division;
			squared_data.x_end /= n_row_division;
			squared_data.y_begin /= n_col_division;
			squared_data.y_end /= n_col_division;
			
			squared_data.saturation = tank.saturation();
			
			squared_data_v.push_back(squared_data);
		}
	}
			
			
	return squared_data_v;
	 
}

std::vector<std::pair<double, double>> simulate::Measure::generate_pressure_vs_y(
	const dst::System& system
)
{
	std::vector<std::pair<double, double>> v;
	
	for(const auto& node: system.state.nodes)
	{
		if(node.is_open_boundary && node.is_inlet)
		{
			v.push_back({node.y, node.calculated.pressure});
		}
	}
	
	std::sort(v.begin(), v.end());
	
	return v;
}

double simulate::Measure::find_average_pressure(
	const dst::System& system
)
{
	double sum = 0;
	for(const auto& node: system.state.nodes)
	{
		if(node.is_open_boundary && node.is_inlet)
		{
			sum += node.calculated.pressure;
		}
	}
	
	return sum / system.parameter.geometry.n_inject_boundaries;
}
