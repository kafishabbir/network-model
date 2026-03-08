#include "output/result.h"

#include "output/latex.h"
#include "output/visual-dimension.h"
#include "output-raster/flow.h"
#include "output-vector/flow.h"
#include <filesystem>
#include <fstream>

const std::string output::Result::folder_run_results_flow = "run/results/flow/";

const std::string output::Result::folder_run_results_flow_figures =
	output::Result::folder_run_results_flow + "figures/";

const std::string output::Result::path_run_results_plots = "run/results/plots/";

const std::string output::Result::file_run_results_plots_data_json =
	output::Result::path_run_results_plots + "data.json";

std::string output::Result::generate_file_name_from_index(const int i)
{
	std::stringstream ss;
	ss << "figure-" << 1000 + i;
	return ss.str();
}

output::Result::Result():
	count_simulations(0),
	count_figures(0),
	json(file_run_results_plots_data_json)
{
	std::filesystem::remove_all(folder_run_results_flow_figures);
	std::filesystem::create_directories(folder_run_results_flow_figures);
	std::filesystem::create_directories(path_run_results_plots);
	std::filesystem::create_directories(folder_run_results_flow + "output/");
	
	const auto& file_name = folder_run_results_flow + "Makefile";
	std::ofstream fout(file_name);
	fout << "all:" << '\n';
	fout << '\t' << "pdflatex -output-directory=output flow" << '\n';
	fout << '\t' << "mv output/flow.pdf flow.pdf" << '\n';
}

output::Result::~Result()
{
	// Dump everything in flow.tex
	std::ifstream fin("template/flow-main.tex");
	if(!fin)
	{
		std::cout << "Error, template/flow-main.tex is missing" << std::endl;
	}

	std::ofstream fout(folder_run_results_flow + "flow.tex");
	fout << fin.rdbuf() << '\n';
	fout << Latex::begin_end_document_scope(ss_flow.str());
}

std::string output::Result::generate_flow_caption(
	const dst::State& state,
	const int count_simulations
)
{
	std::stringstream ss;
	ss << "simulation-id=" << count_simulations << ", ";
	ss << state.reference.comment << ", ";
	ss << "step-id=" << state.reference.id_step << ".";
	
	return ss.str();
}

std::string output::Result::generate_flow_page_text(
	const dst::State& state,
	const dst::SystemOutput& system,
	const int count_simulations
)
{
	std::stringstream ss;
	ss << "\\begin{enumerate}\n";

	// MEASUREMENTS
	ss << "\\item " << "MEASUREMENTS:" << "\n";
	ss << "\\begin{enumerate}\n";
	ss << "\\item time-elapsed=$" << s(state.measured.time_elapsed) << "$,\n";
	ss << "\\item $S=" << s(state.calculated.saturation) << "$,\n";
	ss << "\\item total-fluid-in-system=" << state.calculated.fluid_in_system.str() << ",\n";
	ss << "\\item fluid-added=" << state.measured.fluid_added.str() << ",\n";
	ss << "\\item fluid-evacuated=" << state.measured.fluid_evacuated.str() << ",\n";
	ss << "\\item average-pressure=$" << s(state.calculated.average_pressure) << "$\n";
	ss << "\\end{enumerate}\n";

	// PARAMETER
	ss << "\\item " << "PARAMETER:" << "\n";
	ss << "\\begin{enumerate}\n";
	ss << "\\item constant-physical.sigma=$" << s(system.parameter.constant_physical.sigma) << "$,\n";
	ss << "\\item geometry.radius-contrast=$" << s(system.parameter.geometry.radius_contrast) << "$,\n";
	ss << "\\item constant-physical.viscosity-water=$" << s(system.parameter.constant_physical.viscosity_water) << "$,\n";
	ss << "\\item constant-physical.viscosity-oil=$" << s(system.parameter.constant_physical.viscosity_oil) << "$,\n";
	ss << "\\end{enumerate}\n";

	// TEMPORARY VALUES OF CURRENT STEP
	ss << "\\item " << "TEMPORARY VALUES OF CURRENT STEP:" << "\n";
	ss << "\\begin{enumerate}\n";
	ss << "\\item time-step=$" << s(state.calculated.time_step) << "$,\n";
	ss << "\\item fluid-added=" << state.calculated.fluid_added.str() << ",\n";
	ss << "\\item fluid-evacuated=" << state.calculated.fluid_evacuated.str() << ",\n";
	ss << "\\item $\\Delta V_{t}=" << s(state.calculated.volume_total_delta) << "$,\n";
	ss << "\\item $\\Delta V_{w}=" << s(state.calculated.water_volume_delta) << "$,\n";
	ss << "\\item $\\Delta V_{nw}=" << s(state.calculated.oil_volume_delta) << "$\n";
	ss << "\\end{enumerate}\n";

	ss << "\\end{enumerate}\n";

	return ss.str();
}

std::string output::Result::save_figure_and_generate_inclusion_code(
	const dst::State& state,
	const output::Property& visual_property,
	const std::string& file_name
)
{
	std::stringstream ss;
	const auto& file_full_path = folder_run_results_flow_figures + file_name;
	
	if(state.nodes.size() >= 40)
	{ 
		output_raster::Flow::print_figure(state, file_full_path, visual_property);
		ss << "\\includegraphics[width=0.6\\textwidth]{" << "figures/" << file_name << "}" << '\n';
	}
	else
	{
		output_vector::Flow::save_latex_code_of_figure(state, file_full_path, visual_property);
		ss << "\\input{" << "figures/" << file_name << "}" << '\n';
	}
	
	return ss.str();
}

std::string output::Result::plot_flow(
	const dst::State& state,
	const dst::SystemOutput& system,
	const output::Property& visual_property,
	const int count_figures
)
{
	const auto& file_name = generate_file_name_from_index(count_figures);
	
	const auto& inclusion_code = save_figure_and_generate_inclusion_code(
		state,
		visual_property, 
		file_name
	);
	
	const auto& caption_text = generate_flow_caption(state, count_simulations);
	const auto& page_text = generate_flow_page_text(state, system, count_simulations);
	
	std::stringstream ss;
	
	ss << "\n\\clearpage" << '\n';
	ss << Latex::begin_end_figure_scope(inclusion_code, caption_text, file_name) << '\n';
	ss << page_text << '\n';
	
	return ss.str();
}

void output::Result::add(
	dst::SystemOutput& system,
	const output::Property& visual_property
)
{
	++ count_simulations;

	// Clear page and write the parameters
	ss_flow << "\n\\clearpage" << '\n';
	ss_flow << "Simulation-" << count_simulations << '\n';
	ss_flow << system.parameter.str() << '\n';
	ss_flow << "\\clearpage" << '\n';

	// Add visual-dimensions to the system
	for(auto& state: system.measured.states)
	{
		++ count_figures;
		output::VisualDimension::add_state_visual(state, system, visual_property);
		ss_flow << plot_flow(state, system, visual_property, count_figures) << '\n';
	}
	
	json.add(system, count_simulations);
}
