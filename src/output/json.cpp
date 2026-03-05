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

void output::Json::add(const dst::System& system, int id_simulation)
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

/*
void output::Json::add(const dst::System& system, int id_simulation)
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
	
	
	//~ // Add measured
	sim_json["measured"]["initial_fluid"] = system.measured.initial_fluid.str();
	
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
		//~ state_json["measured"]["time_taken_by_solving_linear_equations"] = state.measured.time_taken_by_solving_linear_equations;
		//~ state_json["measured"]["time_taken_by_each_step"] = state.measured.time_taken_by_each_step;
		//state_json["measured"]["fluid_added"] = state.measured.fluid_added.str();
		//state_json["measured"]["fluid_evacuated"] = state.measured.fluid_evacuated.str();
		
		// Reference
		state_json["reference"]["id_step"] = state.reference.id_step;
		state_json["reference"]["comment"] = state.reference.comment;
		
		// Calculated
		//~ state_json["calculated"]["time_step"] = state.calculated.time_step;
		//~ state_json["calculated"]["fluid_added"] = state.calculated.fluid_added.str();
		//~ state_json["calculated"]["fluid_evacuated"] = state.calculated.fluid_evacuated.str();
		//~ state_json["calculated"]["total_fluid_in_system"] = state.calculated.total_fluid_in_system.str();
		//~ state_json["calculated"]["saturation"] = state.calculated.saturation;
		//~ state_json["calculated"]["volume_total_delta"] = state.calculated.volume_total_delta;
		//~ state_json["calculated"]["water_volume_delta"] = state.calculated.water_volume_delta;
		//~ state_json["calculated"]["oil_volume_delta"] = state.calculated.oil_volume_delta;
		//~ state_json["calculated"]["average_pressure"] = state.calculated.average_pressure;
		
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
		
		//~ // Nodes
		//~ state_json["nodes"] = nlohmann::json::array();
		//~ for (const auto& node : state.nodes) {
			//~ nlohmann::json node_json;
			//~ node_json["x"] = node.x;
			//~ node_json["y"] = node.y;
			//~ node_json["pressure"] = node.pressure;
			//~ node_json["is_open_boundary"] = node.is_open_boundary;
			//~ node_json["is_inlet"] = node.is_inlet;
			//~ node_json["id_fluid_inject"] = node.id_fluid_inject;
			
			//~ node_json["reference"]["connections_id_tube_v"] = node.reference.connections_id_tube_v;
			
			//~ node_json["calculated"]["pressure"] = node.calculated.pressure;
			//~ node_json["calculated"]["tank"] = node.calculated.tank.str();
			//~ node_json["calculated"]["flow_out_id_tube_v"] = node.calculated.flow_out_id_tube_v;
			//~ node_json["calculated"]["volume_fluid_flow_out"] = node.calculated.volume_fluid_flow_out;
			//~ node_json["calculated"]["is_fluid_injected_from_external_to_this_node"] = node.calculated.is_fluid_injected_from_external_to_this_node;
			//~ node_json["calculated"]["id_symmetric_solver"] = node.calculated.id_symmetric_solver;
			//~ node_json["calculated"]["type_fluid_contact"] = node.calculated.type_fluid_contact;
			
			//~ node_json["visual"]["x"] = node.visual.x;
			//~ node_json["visual"]["y"] = node.visual.y;
			//~ node_json["visual"]["radius"] = node.visual.radius;
			
			//~ state_json["nodes"].push_back(node_json);
		//~ }
		
		//~ // Tubes
		//~ state_json["tubes"] = nlohmann::json::array();
		//~ for (const auto& tube : state.tubes) {
			//~ nlohmann::json tube_json;
			//~ tube_json["id_node_first"] = tube.id_node_first;
			//~ tube_json["id_node_second"] = tube.id_node_second;
			//~ tube_json["radius"] = tube.radius;
			//~ tube_json["length"] = tube.length;
			//~ tube_json["mpos"] = tube.mpos;
			//~ tube_json["id_fluid_first"] = tube.id_fluid_first;
			
			//~ tube_json["calculated"]["resistance_coefficient"] = tube.calculated.resistance_coefficient;
			//~ tube_json["calculated"]["capillary_pressure_magnitude"] = tube.calculated.capillary_pressure_magnitude;
			//~ tube_json["calculated"]["flow_rate"] = tube.calculated.flow_rate;
			//~ tube_json["calculated"]["velocity"] = tube.calculated.velocity;
			//~ tube_json["calculated"]["time"] = tube.calculated.time;
			//~ tube_json["calculated"]["is_time_min"] = tube.calculated.is_time_min;
			//~ tube_json["calculated"]["length_displacement_p"] = tube.calculated.length_displacement_p;
			//~ tube_json["calculated"]["volume_displacement"] = tube.calculated.volume_displacement;
			//~ tube_json["calculated"]["id_node_sink"] = tube.calculated.id_node_sink;
			//~ tube_json["calculated"]["tank_pour_into_node"] = tube.calculated.tank_pour_into_node.str();
			//~ tube_json["calculated"]["add_proportion"] = tube.calculated.add_proportion;
			
			//~ tube_json["visual"]["radius"] = tube.visual.radius;
			//~ tube_json["visual"]["length"] = tube.visual.length;
			//~ tube_json["visual"]["mpos"] = tube.visual.mpos;
			
			//~ state_json["tubes"].push_back(tube_json);
		//~ }
		
		sim_json["measured"]["states"].push_back(state_json);
	}
	
	j["simulations"].push_back(sim_json);
}
*/
