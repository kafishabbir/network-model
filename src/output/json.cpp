#include "output/json.h"

#include <nlohmann/json.hpp>
#include <fstream>


void output::Json::write_to_file(const std::string& filename) const
{
    nlohmann::json j;
    
    // Convert your data structure to nlohmann::json format
    j["simulations"] = nlohmann::json::array();

    for(const auto& sim: simulations)
    {
        nlohmann::json sim_json;
        
        sim_json["id"] = sim.id;
        
        // Initial parameter
        sim_json["initial_parameter"] = {
            {"id_fluid_inject", sim.initial_parameter.id_fluid_inject},
            {"sigma", sim.initial_parameter.sigma},
            {"viscosity_ratio", sim.initial_parameter.viscosity_ratio},
            {"radius_contrast", sim.initial_parameter.radius_contrast},
            {"n_tube_rows", sim.initial_parameter.n_tube_rows},
            {"n_tube_cols", sim.initial_parameter.n_tube_cols},
            {"n_periods", sim.initial_parameter.n_periods}
        };
        
        // Network property
        sim_json["network_property"] = {
            {"n_tubes", sim.network_property.n_tubes},
            {"n_nodes", sim.network_property.n_nodes},
            {"radius_average", sim.network_property.radius_average},
            {"radius_min", sim.network_property.radius_min},
            {"radius_max", sim.network_property.radius_max},
            {"radius_ratio", sim.network_property.radius_ratio},
            {"length_average", sim.network_property.length_average},
            {"length_min", sim.network_property.length_min},
            {"length_max", sim.network_property.length_max},
            {"length_ratio", sim.network_property.length_ratio}
        };
        
        // Captures
        sim_json["captures"] = nlohmann::json::array();
        for (const auto& cap : sim.captures) {
            nlohmann::json cap_json;
            cap_json["time"] = cap.time;
            
            cap_json["pressure_vs_y"] = nlohmann::json::array();
            for (const auto& p : cap.pressure_vs_y) {
                cap_json["pressure_vs_y"].push_back({p.first, p.second});
            }
            
            cap_json["saturation_vs_x"] = nlohmann::json::array();
            for (const auto& s : cap.saturation_vs_x) {
                cap_json["saturation_vs_x"].push_back({s.first, s.second});
            }
            
            sim_json["captures"].push_back(cap_json);
        }
        
        // Pressure vs time
        sim_json["time-pressure-saturation-flow-rate"] = nlohmann::json::array();
        for (const auto& pt : sim.high_frequency_data_v) {
            sim_json["time-pressure-saturation-flow-rate"].push_back(
				{pt.time, pt.pressure, pt.saturation, pt.flow_rate});
        }
        
        j["simulations"].push_back(sim_json);
    }
    
    // Write to file
    std::ofstream file(filename);
    file << j.dump(2); // Pretty print with 2-space indentation
}

