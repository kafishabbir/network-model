#include "output/result.h"

#include "output/latex.h"
#include "output/visual-dimension.h"
#include <filesystem>
#include <fstream>

const std::string output::Result::path_flow = "run/results/flow/";

const std::string output::Result::path_folder_figures =
	output::Result::path_flow + "figures/";


std::string output::Result::generate_file_name_from_index(const int i)
{
	std::stringstream ss;
	ss << "figure-" << 1000 + i;
	return ss.str();

}


output::Result::Result():
	count_simulations(0),
	count_figures(0)
{
	std::filesystem::remove_all(path_folder_figures);
	std::filesystem::create_directories(path_folder_figures);
	std::filesystem::create_directories(path_flow + "output/");
	
	const auto& file_name = path_flow + "Makefile";
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

	std::ofstream fout(path_flow + "flow.tex");
	fout << fin.rdbuf() << '\n';

	fout << Latex::begin_end_document_scope(ss_flow.str());
}

std::pair<std::string, std::string> output::Result::generate_flow_caption(
	const nst::State& state,
	const int count_simulations
)
{
    std::stringstream ss1, ss2;
    ss1 << "simulation-id=" << count_simulations << ", ";
    ss1 << state.reference.comment << ", ";
    ss1 << "step-id=" << state.reference.id_step << ".";
	
	ss2 << "\\begin{enumerate}\n";
    
    // MEASUREMENTS
    ss2 << "\\item " << "MEASUREMENTS:" << "\n";
    ss2 << "\\begin{enumerate}\n";
    ss2 << "\\item $S=" << s(state.calculated.saturation) << "$,\n";
    ss2 << "\\item time-elapsed=$" << s(state.measured.time_elapsed) << "$,\n";
    ss2 << "\\item t-fluid-in-system=" << state.calculated.total_fluid_in_system.str() << ",\n";
    ss2 << "\\item t-fluid-added=" << state.measured.total_fluid_added.str() << ",\n";
    ss2 << "\\item t-fluid-evacuated=" << state.measured.total_fluid_evacuated.str() << "\n";
    ss2 << "\\end{enumerate}\n";
    
    // SIMULATION PARAMETERS
    ss2 << "\\item " << "SIMULATION PARAMETERS:" << "\n";
    ss2 << "\\begin{enumerate}\n";
    ss2 << "\\item $\\sigma=" << s(state.physical_constant.sigma) << "$,\n";
    ss2 << "\\item $\\mu_{w}=" << s(state.water_viscosity()) << "$,\n";
    ss2 << "\\item $\\mu_{nw}=" << s(state.oil_viscosity()) << "$,\n";
    ss2 << "\\item time step resolution=$" << s(state.simulation_constant.time_step_resolution) << "$,\n";
    ss2 << "\\end{enumerate}\n";
    
    // NETWORK CHARACTERISTICS
    ss2 << "\\item " << "NETWORK CHARACTERISTICS:" << "\n";
    ss2 << "\\begin{enumerate}\n";
    ss2 << "\\item $R_{min} / R_{max} =" << -1 << "$ (add-later),\n";
    ss2 << "\\item $l_{min} / l_{max} =" << -1 << "$ (add-later),\n";
    ss2 << "\\item $n_{nodes}=" << state.nodes.size() << "$,\n";
    ss2 << "\\item $n_{tubes}=" << state.tubes.size() << "$\n";
    ss2 << "\\end{enumerate}\n";
    
    // TEMPORARY VALUES OF CURRENT STEP
    ss2 << "\\item " << "TEMPORARY VALUES OF CURRENT STEP:" << "\n";
    ss2 << "\\begin{enumerate}\n";
    ss2 << "\\item time-step=$" << s(state.calculated.time_step) << "$,\n";
    ss2 << "\\item fluid-added=" << state.calculated.fluid_added.str() << ",\n";
    ss2 << "\\item fluid-evacuated=" << state.calculated.fluid_evacuated.str() << ",\n";
    ss2 << "\\end{enumerate}\n";
    
    // ACCURACY
    ss2 << "\\item " << "ACCURACY:" << "\n";
    ss2 << "\\begin{enumerate}\n";
    ss2 << "\\item $\\Delta V_{t}=" << s(state.calculated.volume_total_delta) << "$,\n";
    ss2 << "\\item $\\Delta V_{w}=" << s(state.calculated.water_volume_delta) << "$,\n";
    ss2 << "\\item $\\Delta V_{nw}=" << s(state.calculated.oil_volume_delta) << "$.\n";
    ss2 << "\\end{enumerate}\n";

ss2 << "\\end{enumerate}\n";

    return {ss1.str(), ss2.str()};
}

std::string output::Result::plot_flow(
	const nst::State& state,
	const output::Property& visual_property,
	const int count_figures
)
{
	const auto& file_name = generate_file_name_from_index(count_figures);
	const auto& file_full_path = path_folder_figures + file_name;

	std::stringstream ss, ss_final;
	if(state.nodes.size() >= 20)
	{ 
		output_raster::Flow::print_figure(state, file_full_path, visual_property);
		ss << "\\includegraphics[width=0.6\\textwidth]{" << "figures/" << file_name << "}" << '\n';
	}
	else
	{
		output_vector::Flow::save_latex_code_of_figure(state, file_full_path, visual_property);
		ss << "\\input{" << "figures/" << file_name << "}" << '\n';
	}

	const auto& [caption_text, page_text] = generate_flow_caption(state, count_simulations);
	
	ss_final << "\n\\clearpage" << '\n';
	ss_final << Latex::begin_end_figure_scope(ss.str(), caption_text, file_name) << '\n';
	ss_final << page_text << '\n';
	return ss_final.str();
}


void output::Result::add(
	dst::States& states,
	const simulate::Property& simulate_property,
	const output::Property& visual_property
)
{
	++ count_simulations;

	ss_flow << "\n\\clearpage" << '\n';
	ss_flow << "Simulation-" << count_simulations << '\n';
	ss_flow << simulate_property.str();
	ss_flow << "\\clearpage" << '\n';

	for(auto& state: states)
	{
		output::VisualDimension::add_state_visual(state, visual_property);
	}

	// Generate the visualizations of the flows
	for(const auto& state: states)
	{
		++ count_figures;
		ss_flow << plot_flow(state, visual_property, count_figures) << '\n';
	}

}

