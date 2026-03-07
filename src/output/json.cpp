#include "output/json.h"
#include <fstream>


output::Json::Json(const std::string& file_name):
	file_name(file_name)
{
	j["simulations"] = nlohmann::json::array();
}

output::Json::~Json()
{
	std::ofstream fout(file_name);
	fout <<  j.dump(2);
}

void output::Json::add(const dst::SystemOutput& system, int id_simulation)
{
	nlohmann::json sim_json;
	
	sim_json["id"] = id_simulation;
	
	// Add the ENTIRE parameter struct
	sim_json["parameter"]["simulation"] = {
		{"is_flow_as_opposed_to_test", system.parameter.simulation.is_flow_as_opposed_to_test},
		{"is_flow_const_flow_rate", system.parameter.simulation.is_flow_const_flow_rate},
		{"is_const_porosity", system.parameter.simulation.is_const_porosity},
		{"id_fluid_inject", system.parameter.simulation.id_fluid_inject},
		{"inlet_pressure", system.parameter.simulation.inlet_pressure}
	};
	
	sim_json["parameter"]["geometry"] = {
		{"n_tube_rows", system.parameter.geometry.n_tube_rows},
		{"n_tube_cols", system.parameter.geometry.n_tube_cols},
		{"radius_contrast", system.parameter.geometry.radius_contrast},
		{"length_scale", system.parameter.geometry.length_scale},
		{"n_periods", system.parameter.geometry.n_periods},
		{"n_inject_boundaries", system.parameter.geometry.n_inject_boundaries}
	};
	
	sim_json["parameter"]["geometry_distributions"]["radius"] = {
		{"average", system.parameter.geometry_distributions.radius.average},
		{"min", system.parameter.geometry_distributions.radius.min},
		{"max", system.parameter.geometry_distributions.radius.max},
		{"variance", system.parameter.geometry_distributions.radius.variance}
	};
	
	sim_json["parameter"]["geometry_distributions"]["length"] = {
		{"average", system.parameter.geometry_distributions.length.average},
		{"min", system.parameter.geometry_distributions.length.min},
		{"max", system.parameter.geometry_distributions.length.max},
		{"variance", system.parameter.geometry_distributions.length.variance}
	};
	
	sim_json["parameter"]["geometry_distributions"]["volume"] = {
		{"average", system.parameter.geometry_distributions.volume.average},
		{"min", system.parameter.geometry_distributions.volume.min},
		{"max", system.parameter.geometry_distributions.volume.max},
		{"variance", system.parameter.geometry_distributions.volume.variance}
	};
	
	sim_json["parameter"]["constant_physical"] = {
		{"sigma", system.parameter.constant_physical.sigma},
		{"viscosity_water", system.parameter.constant_physical.viscosity_water},
		{"viscosity_oil", system.parameter.constant_physical.viscosity_oil}
	};
	
	sim_json["parameter"]["constant_computational"] = {
		{"time_step_resolution", system.parameter.constant_computational.time_step_resolution}
	};
	
	sim_json["parameter"]["plot"] = {
		{"volume_max_to_inject", system.parameter.plot.volume_max_to_inject},
		{"capture_frequency_in_volume_fraction", system.parameter.plot.capture_frequency_in_volume_fraction}
	};
	
	
	sim_json["measured"]["high_frequency_data_v"] = nlohmann::json::array();
	for (const auto& hf : system.measured.high_frequency_data_v) {
		sim_json["measured"]["high_frequency_data_v"].push_back({
			{"time", hf.time},
			{"pressure", hf.pressure},
			{"saturation", hf.saturation},
			{"flow_rate", hf.flow_rate}
		});
	}
	
	sim_json["measured"]["states"] = nlohmann::json::array();
	for (const auto& state : system.measured.states) {
		nlohmann::json state_json;
		// Measured
		state_json["measured"]["time_elapsed"] = state.measured.time_elapsed;

		// Reference
		state_json["reference"]["id_step"] = state.reference.id_step;
		state_json["reference"]["comment"] = state.reference.comment;
		

		// pressure_vs_y
		state_json["calculated"]["pressure_vs_y"] = nlohmann::json::array();
		for (const auto& p : state.calculated.pressure_vs_y) {
			state_json["calculated"]["pressure_vs_y"].push_back({p.first, p.second});
		}
		
		// saturation_vs_x
		state_json["calculated"]["saturation_vs_x"] = nlohmann::json::array();
		for (const auto& s : state.calculated.saturation_vs_x) {
			state_json["calculated"]["saturation_vs_x"].push_back({s.first, s.second});
		}
		
		sim_json["measured"]["states"].push_back(state_json);
	}
	
	j["simulations"].push_back(sim_json);
}
