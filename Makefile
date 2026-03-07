

all: folder_check compile_necessary run_program
	@echo "Command executed = all"
	@echo " "


folder_check:
	mkdir -p run/
	mkdir -p run/build/
	@echo "Command executed = folder_check"
	@echo " "


compile_necessary: run/simulate.exe
	@echo "Command executed = compile_necessary"
	@echo " "


run_program:
	./run/simulate.exe


force: folder_check clear_build compile_necessary run_program
	@echo "Command executed = force"
	@echo " "


clear_build:
	rm -rf run/build/*
	@echo "Command executed = force"
	@echo " "


edit:
	geany -i  src/dst/measured.cpp src/dst/measured.h src/dst/parameter.cpp src/dst/parameter.h src/dst/state.cpp src/dst/state.h src/dst/system.cpp src/dst/system.h src/dst/system-output.cpp src/dst/system-output.h src/exe/simulate.cpp src/global/decl.h src/ic/geometry-base.cpp src/ic/geometry-base.h src/ic/geometry-flow.cpp src/ic/geometry-flow.h src/ic/geometry-rand.cpp src/ic/geometry-rand.h src/nst/node.cpp src/nst/node.h src/nst/tank.cpp src/nst/tank.h src/nst/tube.cpp src/nst/tube.h src/output-raster/cairo.cpp src/output-raster/cairo.h src/output-raster/flow.cpp src/output-raster/flow.h src/output-vector/draw.cpp src/output-vector/draw.h src/output-vector/flow.cpp src/output-vector/flow.h src/output-vector/label-node.cpp src/output-vector/label-node.h src/output-vector/label-tube.cpp src/output-vector/label-tube.h src/output-vector/tikz.cpp src/output-vector/tikz.h src/output/json.cpp src/output/json.h src/output/latex.cpp src/output/latex.h src/output/property.cpp src/output/property.h src/output/result.cpp src/output/result.h src/output/visual-dimension.cpp src/output/visual-dimension.h src/program/debug-flow.cpp src/program/debug-flow.h src/program/flow-in-periodic-medium.cpp src/program/flow-in-periodic-medium.h src/program/function-trial.cpp src/program/function-trial.h src/program/permeability.cpp src/program/permeability.h src/simulate/assign.cpp src/simulate/assign.h src/simulate/capture.cpp src/simulate/capture.h src/simulate/measure.cpp src/simulate/measure.h src/simulate/menu.cpp src/simulate/menu.h src/simulate/preparation.cpp src/simulate/preparation.h src/simulate/set-solver.cpp src/simulate/set-solver.h src/simulate/system-generator.cpp src/simulate/system-generator.h src/step/all-parts.cpp src/step/all-parts.h src/step/part01-reference.cpp src/step/part01-reference.h src/step/part02-pressure.cpp src/step/part02-pressure.h src/step/part03-velocity.cpp src/step/part03-velocity.h src/step/part04-time.cpp src/step/part04-time.h src/step/part05-displacement.cpp src/step/part05-displacement.h src/step/part06-pour.cpp src/step/part06-pour.h src/step/part07-inject.cpp src/step/part07-inject.h src/step/part08-distribute.cpp src/step/part08-distribute.h src/step/part09-displace.cpp src/step/part09-displace.h src/step/part10-measure.cpp src/step/part10-measure.h src/utility/random.cpp src/utility/random.h src/utility/str.cpp src/utility/str.h src/utility/time.cpp src/utility/time.h


run/simulate.exe: run/build/exe_simulate.o run/build/dst_measured.o run/build/dst_parameter.o run/build/dst_state.o run/build/dst_system.o run/build/dst_system-output.o run/build/ic_geometry-base.o run/build/ic_geometry-flow.o run/build/ic_geometry-rand.o run/build/nst_node.o run/build/nst_tank.o run/build/nst_tube.o run/build/output-raster_cairo.o run/build/output-raster_flow.o run/build/output-vector_draw.o run/build/output-vector_flow.o run/build/output-vector_label-node.o run/build/output-vector_label-tube.o run/build/output-vector_tikz.o run/build/output_json.o run/build/output_latex.o run/build/output_property.o run/build/output_result.o run/build/output_visual-dimension.o run/build/program_debug-flow.o run/build/program_flow-in-periodic-medium.o run/build/program_function-trial.o run/build/program_permeability.o run/build/simulate_assign.o run/build/simulate_capture.o run/build/simulate_measure.o run/build/simulate_menu.o run/build/simulate_preparation.o run/build/simulate_set-solver.o run/build/simulate_system-generator.o run/build/step_all-parts.o run/build/step_part01-reference.o run/build/step_part02-pressure.o run/build/step_part03-velocity.o run/build/step_part04-time.o run/build/step_part05-displacement.o run/build/step_part06-pour.o run/build/step_part07-inject.o run/build/step_part08-distribute.o run/build/step_part09-displace.o run/build/step_part10-measure.o run/build/utility_random.o run/build/utility_str.o run/build/utility_time.o
	g++  run/build/exe_simulate.o run/build/dst_measured.o run/build/dst_parameter.o run/build/dst_state.o run/build/dst_system.o run/build/dst_system-output.o run/build/ic_geometry-base.o run/build/ic_geometry-flow.o run/build/ic_geometry-rand.o run/build/nst_node.o run/build/nst_tank.o run/build/nst_tube.o run/build/output-raster_cairo.o run/build/output-raster_flow.o run/build/output-vector_draw.o run/build/output-vector_flow.o run/build/output-vector_label-node.o run/build/output-vector_label-tube.o run/build/output-vector_tikz.o run/build/output_json.o run/build/output_latex.o run/build/output_property.o run/build/output_result.o run/build/output_visual-dimension.o run/build/program_debug-flow.o run/build/program_flow-in-periodic-medium.o run/build/program_function-trial.o run/build/program_permeability.o run/build/simulate_assign.o run/build/simulate_capture.o run/build/simulate_measure.o run/build/simulate_menu.o run/build/simulate_preparation.o run/build/simulate_set-solver.o run/build/simulate_system-generator.o run/build/step_all-parts.o run/build/step_part01-reference.o run/build/step_part02-pressure.o run/build/step_part03-velocity.o run/build/step_part04-time.o run/build/step_part05-displacement.o run/build/step_part06-pour.o run/build/step_part07-inject.o run/build/step_part08-distribute.o run/build/step_part09-displace.o run/build/step_part10-measure.o run/build/utility_random.o run/build/utility_str.o run/build/utility_time.o -o run/simulate.exe -lcairo
	@echo "run/simulate.exe created."
	@echo " "


run/build/dst_measured.o: src/dst/measured.cpp src/dst/measured.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/dst/measured.cpp -o run/build/dst_measured.o
	@echo "run/build/dst_measured.o created."
	@echo " "


run/build/dst_parameter.o: src/dst/parameter.cpp src/dst/parameter.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/dst/parameter.cpp -o run/build/dst_parameter.o
	@echo "run/build/dst_parameter.o created."
	@echo " "


run/build/dst_state.o: src/dst/state.cpp src/dst/state.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/dst/state.cpp -o run/build/dst_state.o
	@echo "run/build/dst_state.o created."
	@echo " "


run/build/dst_system.o: src/dst/system.cpp src/dst/system.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/dst/system.cpp -o run/build/dst_system.o
	@echo "run/build/dst_system.o created."
	@echo " "


run/build/dst_system-output.o: src/dst/system-output.cpp src/dst/system-output.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/dst/system-output.cpp -o run/build/dst_system-output.o
	@echo "run/build/dst_system-output.o created."
	@echo " "


run/build/exe_simulate.o: src/exe/simulate.cpp src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/simulate.cpp -o run/build/exe_simulate.o
	@echo "run/build/exe_simulate.o created."
	@echo " "


run/build/ic_geometry-base.o: src/ic/geometry-base.cpp src/ic/geometry-base.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/ic/geometry-base.cpp -o run/build/ic_geometry-base.o
	@echo "run/build/ic_geometry-base.o created."
	@echo " "


run/build/ic_geometry-flow.o: src/ic/geometry-flow.cpp src/ic/geometry-flow.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/ic/geometry-flow.cpp -o run/build/ic_geometry-flow.o
	@echo "run/build/ic_geometry-flow.o created."
	@echo " "


run/build/ic_geometry-rand.o: src/ic/geometry-rand.cpp src/ic/geometry-rand.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/ic/geometry-rand.cpp -o run/build/ic_geometry-rand.o
	@echo "run/build/ic_geometry-rand.o created."
	@echo " "


run/build/nst_node.o: src/nst/node.cpp src/nst/node.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/node.cpp -o run/build/nst_node.o
	@echo "run/build/nst_node.o created."
	@echo " "


run/build/nst_tank.o: src/nst/tank.cpp src/nst/tank.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/tank.cpp -o run/build/nst_tank.o
	@echo "run/build/nst_tank.o created."
	@echo " "


run/build/nst_tube.o: src/nst/tube.cpp src/nst/tube.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/tube.cpp -o run/build/nst_tube.o
	@echo "run/build/nst_tube.o created."
	@echo " "


run/build/output-raster_cairo.o: src/output-raster/cairo.cpp src/output-raster/cairo.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-raster/cairo.cpp -o run/build/output-raster_cairo.o
	@echo "run/build/output-raster_cairo.o created."
	@echo " "


run/build/output-raster_flow.o: src/output-raster/flow.cpp src/output-raster/flow.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-raster/flow.cpp -o run/build/output-raster_flow.o
	@echo "run/build/output-raster_flow.o created."
	@echo " "


run/build/output-vector_draw.o: src/output-vector/draw.cpp src/output-vector/draw.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-vector/draw.cpp -o run/build/output-vector_draw.o
	@echo "run/build/output-vector_draw.o created."
	@echo " "


run/build/output-vector_flow.o: src/output-vector/flow.cpp src/output-vector/flow.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-vector/flow.cpp -o run/build/output-vector_flow.o
	@echo "run/build/output-vector_flow.o created."
	@echo " "


run/build/output-vector_label-node.o: src/output-vector/label-node.cpp src/output-vector/label-node.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-vector/label-node.cpp -o run/build/output-vector_label-node.o
	@echo "run/build/output-vector_label-node.o created."
	@echo " "


run/build/output-vector_label-tube.o: src/output-vector/label-tube.cpp src/output-vector/label-tube.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-vector/label-tube.cpp -o run/build/output-vector_label-tube.o
	@echo "run/build/output-vector_label-tube.o created."
	@echo " "


run/build/output-vector_tikz.o: src/output-vector/tikz.cpp src/output-vector/tikz.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-vector/tikz.cpp -o run/build/output-vector_tikz.o
	@echo "run/build/output-vector_tikz.o created."
	@echo " "


run/build/output_json.o: src/output/json.cpp src/output/json.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output/json.cpp -o run/build/output_json.o
	@echo "run/build/output_json.o created."
	@echo " "


run/build/output_latex.o: src/output/latex.cpp src/output/latex.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output/latex.cpp -o run/build/output_latex.o
	@echo "run/build/output_latex.o created."
	@echo " "


run/build/output_property.o: src/output/property.cpp src/output/property.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output/property.cpp -o run/build/output_property.o
	@echo "run/build/output_property.o created."
	@echo " "


run/build/output_result.o: src/output/result.cpp src/output/result.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output/result.cpp -o run/build/output_result.o
	@echo "run/build/output_result.o created."
	@echo " "


run/build/output_visual-dimension.o: src/output/visual-dimension.cpp src/output/visual-dimension.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output/visual-dimension.cpp -o run/build/output_visual-dimension.o
	@echo "run/build/output_visual-dimension.o created."
	@echo " "


run/build/program_debug-flow.o: src/program/debug-flow.cpp src/program/debug-flow.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/program/debug-flow.cpp -o run/build/program_debug-flow.o
	@echo "run/build/program_debug-flow.o created."
	@echo " "


run/build/program_flow-in-periodic-medium.o: src/program/flow-in-periodic-medium.cpp src/program/flow-in-periodic-medium.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/program/flow-in-periodic-medium.cpp -o run/build/program_flow-in-periodic-medium.o
	@echo "run/build/program_flow-in-periodic-medium.o created."
	@echo " "


run/build/program_function-trial.o: src/program/function-trial.cpp src/program/function-trial.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/program/function-trial.cpp -o run/build/program_function-trial.o
	@echo "run/build/program_function-trial.o created."
	@echo " "


run/build/program_permeability.o: src/program/permeability.cpp src/program/permeability.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/program/permeability.cpp -o run/build/program_permeability.o
	@echo "run/build/program_permeability.o created."
	@echo " "


run/build/simulate_assign.o: src/simulate/assign.cpp src/simulate/assign.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/assign.cpp -o run/build/simulate_assign.o
	@echo "run/build/simulate_assign.o created."
	@echo " "


run/build/simulate_capture.o: src/simulate/capture.cpp src/simulate/capture.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/capture.cpp -o run/build/simulate_capture.o
	@echo "run/build/simulate_capture.o created."
	@echo " "


run/build/simulate_measure.o: src/simulate/measure.cpp src/simulate/measure.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/measure.cpp -o run/build/simulate_measure.o
	@echo "run/build/simulate_measure.o created."
	@echo " "


run/build/simulate_menu.o: src/simulate/menu.cpp src/simulate/menu.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/menu.cpp -o run/build/simulate_menu.o
	@echo "run/build/simulate_menu.o created."
	@echo " "


run/build/simulate_preparation.o: src/simulate/preparation.cpp src/simulate/preparation.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/preparation.cpp -o run/build/simulate_preparation.o
	@echo "run/build/simulate_preparation.o created."
	@echo " "


run/build/simulate_set-solver.o: src/simulate/set-solver.cpp src/simulate/set-solver.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/set-solver.cpp -o run/build/simulate_set-solver.o
	@echo "run/build/simulate_set-solver.o created."
	@echo " "


run/build/simulate_system-generator.o: src/simulate/system-generator.cpp src/simulate/system-generator.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/system-generator.cpp -o run/build/simulate_system-generator.o
	@echo "run/build/simulate_system-generator.o created."
	@echo " "


run/build/step_all-parts.o: src/step/all-parts.cpp src/step/all-parts.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/step/all-parts.cpp -o run/build/step_all-parts.o
	@echo "run/build/step_all-parts.o created."
	@echo " "


run/build/step_part01-reference.o: src/step/part01-reference.cpp src/step/part01-reference.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/step/part01-reference.cpp -o run/build/step_part01-reference.o
	@echo "run/build/step_part01-reference.o created."
	@echo " "


run/build/step_part02-pressure.o: src/step/part02-pressure.cpp src/step/part02-pressure.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/step/part02-pressure.cpp -o run/build/step_part02-pressure.o
	@echo "run/build/step_part02-pressure.o created."
	@echo " "


run/build/step_part03-velocity.o: src/step/part03-velocity.cpp src/step/part03-velocity.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/step/part03-velocity.cpp -o run/build/step_part03-velocity.o
	@echo "run/build/step_part03-velocity.o created."
	@echo " "


run/build/step_part04-time.o: src/step/part04-time.cpp src/step/part04-time.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/step/part04-time.cpp -o run/build/step_part04-time.o
	@echo "run/build/step_part04-time.o created."
	@echo " "


run/build/step_part05-displacement.o: src/step/part05-displacement.cpp src/step/part05-displacement.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/step/part05-displacement.cpp -o run/build/step_part05-displacement.o
	@echo "run/build/step_part05-displacement.o created."
	@echo " "


run/build/step_part06-pour.o: src/step/part06-pour.cpp src/step/part06-pour.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/step/part06-pour.cpp -o run/build/step_part06-pour.o
	@echo "run/build/step_part06-pour.o created."
	@echo " "


run/build/step_part07-inject.o: src/step/part07-inject.cpp src/step/part07-inject.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/step/part07-inject.cpp -o run/build/step_part07-inject.o
	@echo "run/build/step_part07-inject.o created."
	@echo " "


run/build/step_part08-distribute.o: src/step/part08-distribute.cpp src/step/part08-distribute.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/step/part08-distribute.cpp -o run/build/step_part08-distribute.o
	@echo "run/build/step_part08-distribute.o created."
	@echo " "


run/build/step_part09-displace.o: src/step/part09-displace.cpp src/step/part09-displace.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/step/part09-displace.cpp -o run/build/step_part09-displace.o
	@echo "run/build/step_part09-displace.o created."
	@echo " "


run/build/step_part10-measure.o: src/step/part10-measure.cpp src/step/part10-measure.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/step/part10-measure.cpp -o run/build/step_part10-measure.o
	@echo "run/build/step_part10-measure.o created."
	@echo " "


run/build/utility_random.o: src/utility/random.cpp src/utility/random.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/utility/random.cpp -o run/build/utility_random.o
	@echo "run/build/utility_random.o created."
	@echo " "


run/build/utility_str.o: src/utility/str.cpp src/utility/str.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/utility/str.cpp -o run/build/utility_str.o
	@echo "run/build/utility_str.o created."
	@echo " "


run/build/utility_time.o: src/utility/time.cpp src/utility/time.h src/global/decl.h
	g++ -c -Wall -std=c++17 -Isrc/ src/utility/time.cpp -o run/build/utility_time.o
	@echo "run/build/utility_time.o created."
	@echo " "
