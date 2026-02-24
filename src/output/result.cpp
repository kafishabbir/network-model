#include "output/result.h"
#include "utility/str.h"
#include "output/latex.h"
#include "output/visual-dimension.h"

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
	count_simulations(0)
	count_figures(0)
{
	std::filesystem::remove_all(path_folder_figures);
	std::filesystem::create_directories(path_folder_figures);
	std::filesystem::create_directories(path_flow + "output/");

	std::ofstream fout(path_flow + "Makefile");
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

std::string output::Result::generate_flow_caption(
	const nst::State& state,
	const int count_simulations
)
{
	auto str_l = utility::Str::latex;
	auto str = utility::Str::str;


    std::stringstream ss;
    ss << "simulation-id=" << count_simulations << ", ";
    ss << state.reference.comment << ", ";
    ss << "step-id=" << state.reference.id_step << ", ";


    ss << "MEASUREMENTS: ";
    ss << "$S=" << str_l(state.calculated.saturation) << "$, ";
    ss << "time-elapsed=$" << str_l(state.measured.time_elapsed) << "$" << ", ";
    ss << "t-fluid-in-system=" << str(state.calculated.total_fluid_in_system) << ", ";
    ss << "t-fluid-added=" << str(state.measured.total_fluid_added) << ", ";
    ss << "t-fluid-evacuated=" << str(state.measured.total_fluid_evacuated) << ", ";


	ss << "SIMULATION PARAMETERS: ";
	ss << "$\\sigma=" << str_l(state.physical_constant.sigma) << "$" << ", ";
	ss << "$\\mu_{w}=" << str_l(state.water_viscosity()) << "$" << ", ";
    ss << "$\\mu_{nw}=" << str_l(state.oil_viscosity()) << "$" << ", ";
    ss << "time step resolution=$" << str_l(state.simulation_constant.time_step_resolution) << "$" << ", ";


	ss << "NETWORK CHARACTERSTICS: ";
	ss << "$R_{min} / R_{max} =" << -1 << "$" << "(add-later), ";
    ss << "$l_{min} / l_{max} =" << -1 << "$" << "(add-later), ";
	ss << "$n_{nodes}=" << state.nodes.size() << "$" << ", ";
    ss << "$n_{tubes}=" << state.tubes.size() << "$" << ", ";


	ss << "TEMPORARY VALUES OF CURRENT STEP: ";
    ss << "time-step=$" << str_l(state.calculated.time_step) << "$" << ", ";
    ss << "fluid-added=" << str(state.calculated.fluid_added) << ", ";
    ss << "fluid-evacuated=" << str(state.calculated.fluid_evacuated) << ", ";


    ss << "ACCURACY: ";
    ss << "$\\Delta V_{t}=" << str_l(state.calculated.volume_total_delta) << "$, ";
    ss << "$\\Delta V_{w}=" << str_l(state.calculated.water_volume_delta) << "$, ";
    ss << "$\\Delta V_{nw}=" << str_l(state.calculated.oil_volume_delta) << "$, ";


    return ss.str();
}

std::string output::Result::plot_flow(
	const nst::State& state,
	const output::Property& visual_property,
	const int count_figures
)
{
	const auto& file_name = generate_file_name_from_index(count_figures);
	const auto& file_full_path = path_folder_figures + file_name;

	std::stringstream ss;
	if(state.nodes.size() >= 10)
	{
		output_raster::Flow::print_figure(state, visual_property, file_full_path);
		ss << "\\includegraphics[width=0.6\\textwidth]{" << "figures/" << file_name << "}" << '\n';
	}
	else
	{
		output_vector::Flow::save_latex_code_of_figure(state, visual_property, file_full_path);
		ss << "\\include{" << "figures/" << file_name << "}" << '\n';
	}

	const auto& caption_text = generate_flow_caption(state, count_simulations);

	return Latex::begin_end_figure_scope(ss.str(), caption_text, file_name);
}


void output::Result::add(
	dst::States& states,
	const simulate::Property& simulate_property,
	const output::Property& visual_property
)
{
	++ count_simulations;

	ss_flow << "\\clearpage" << '\n';
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
		ss_flow << plot_flow(state, simulate_property, count_figures) << '\n';
	}

}

