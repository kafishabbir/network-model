

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
	geany -i  src/exe/simulate.cpp src/global/decl.h src/global/dst.h src/ic/geometry-base.cpp src/ic/geometry-base.h src/ic/geometry-flow.cpp src/ic/geometry-flow.h src/ic/geometry-rand.cpp src/ic/geometry-rand.h src/nst/fluid.cpp src/nst/fluid.h src/nst/node.cpp src/nst/node.h src/nst/state.cpp src/nst/state.h src/nst/tank.cpp src/nst/tank.h src/nst/tube.cpp src/nst/tube.h src/output-raster/cairo.cpp src/output-raster/cairo.h src/output-raster/flow.cpp src/output-raster/flow.h src/output-vector/draw.cpp src/output-vector/draw.h src/output-vector/flow.cpp src/output-vector/flow.h src/output-vector/label-node.cpp src/output-vector/label-node.h src/output-vector/label-tube.cpp src/output-vector/label-tube.h src/output-vector/tikz.cpp src/output-vector/tikz.h src/output/latex.cpp src/output/latex.h src/output/property.cpp src/output/property.h src/output/result.cpp src/output/result.h src/output/visual-dimension.cpp src/output/visual-dimension.h src/program/debug-flow.cpp src/program/debug-flow.h src/program/flow-in-periodic-medium.cpp src/program/flow-in-periodic-medium.h src/program/function-trial.cpp src/program/function-trial.h src/simulate/menu.cpp src/simulate/menu.h src/simulate/property.cpp src/simulate/property.h src/simulate/step0-preparation.cpp src/simulate/step0-preparation.h src/simulate/step1-tube-flow-coefficient.cpp src/simulate/step1-tube-flow-coefficient.h src/simulate/step10-measure.cpp src/simulate/step10-measure.h src/simulate/step2-pressure.cpp src/simulate/step2-pressure.h src/simulate/step3-velocity.cpp src/simulate/step3-velocity.h src/simulate/step4-time-step.cpp src/simulate/step4-time-step.h src/simulate/step5-displacement.cpp src/simulate/step5-displacement.h src/simulate/step6-pour-into-node.cpp src/simulate/step6-pour-into-node.h src/simulate/step7-inject-evacuate.cpp src/simulate/step7-inject-evacuate.h src/simulate/step8-distribute.cpp src/simulate/step8-distribute.h src/simulate/step9-update-tube-mpos.cpp src/simulate/step9-update-tube-mpos.h src/simulate/utility.cpp src/simulate/utility.h src/utility/math.cpp src/utility/math.h src/utility/measure.cpp src/utility/measure.h src/utility/random.cpp src/utility/random.h src/utility/str.cpp src/utility/str.h src/utility/time.cpp src/utility/time.h


run/simulate.exe: run/build/exe_simulate.o run/build/ic_geometry-base.o run/build/ic_geometry-flow.o run/build/ic_geometry-rand.o run/build/nst_fluid.o run/build/nst_node.o run/build/nst_state.o run/build/nst_tank.o run/build/nst_tube.o run/build/output-raster_cairo.o run/build/output-raster_flow.o run/build/output-vector_draw.o run/build/output-vector_flow.o run/build/output-vector_label-node.o run/build/output-vector_label-tube.o run/build/output-vector_tikz.o run/build/output_latex.o run/build/output_property.o run/build/output_result.o run/build/output_visual-dimension.o run/build/program_debug-flow.o run/build/program_flow-in-periodic-medium.o run/build/program_function-trial.o run/build/simulate_menu.o run/build/simulate_property.o run/build/simulate_step0-preparation.o run/build/simulate_step1-tube-flow-coefficient.o run/build/simulate_step10-measure.o run/build/simulate_step2-pressure.o run/build/simulate_step3-velocity.o run/build/simulate_step4-time-step.o run/build/simulate_step5-displacement.o run/build/simulate_step6-pour-into-node.o run/build/simulate_step7-inject-evacuate.o run/build/simulate_step8-distribute.o run/build/simulate_step9-update-tube-mpos.o run/build/simulate_utility.o run/build/utility_math.o run/build/utility_measure.o run/build/utility_random.o run/build/utility_str.o run/build/utility_time.o
	g++  run/build/exe_simulate.o run/build/ic_geometry-base.o run/build/ic_geometry-flow.o run/build/ic_geometry-rand.o run/build/nst_fluid.o run/build/nst_node.o run/build/nst_state.o run/build/nst_tank.o run/build/nst_tube.o run/build/output-raster_cairo.o run/build/output-raster_flow.o run/build/output-vector_draw.o run/build/output-vector_flow.o run/build/output-vector_label-node.o run/build/output-vector_label-tube.o run/build/output-vector_tikz.o run/build/output_latex.o run/build/output_property.o run/build/output_result.o run/build/output_visual-dimension.o run/build/program_debug-flow.o run/build/program_flow-in-periodic-medium.o run/build/program_function-trial.o run/build/simulate_menu.o run/build/simulate_property.o run/build/simulate_step0-preparation.o run/build/simulate_step1-tube-flow-coefficient.o run/build/simulate_step10-measure.o run/build/simulate_step2-pressure.o run/build/simulate_step3-velocity.o run/build/simulate_step4-time-step.o run/build/simulate_step5-displacement.o run/build/simulate_step6-pour-into-node.o run/build/simulate_step7-inject-evacuate.o run/build/simulate_step8-distribute.o run/build/simulate_step9-update-tube-mpos.o run/build/simulate_utility.o run/build/utility_math.o run/build/utility_measure.o run/build/utility_random.o run/build/utility_str.o run/build/utility_time.o -o run/simulate.exe -lcairo
	@echo "run/simulate.exe created."
	@echo " "


run/build/exe_simulate.o: src/exe/simulate.cpp src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/simulate.cpp -o run/build/exe_simulate.o
	@echo "run/build/exe_simulate.o created."
	@echo " "


run/build/ic_geometry-base.o: src/ic/geometry-base.cpp src/ic/geometry-base.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/ic/geometry-base.cpp -o run/build/ic_geometry-base.o
	@echo "run/build/ic_geometry-base.o created."
	@echo " "


run/build/ic_geometry-flow.o: src/ic/geometry-flow.cpp src/ic/geometry-flow.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/ic/geometry-flow.cpp -o run/build/ic_geometry-flow.o
	@echo "run/build/ic_geometry-flow.o created."
	@echo " "


run/build/ic_geometry-rand.o: src/ic/geometry-rand.cpp src/ic/geometry-rand.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/ic/geometry-rand.cpp -o run/build/ic_geometry-rand.o
	@echo "run/build/ic_geometry-rand.o created."
	@echo " "


run/build/nst_fluid.o: src/nst/fluid.cpp src/nst/fluid.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/fluid.cpp -o run/build/nst_fluid.o
	@echo "run/build/nst_fluid.o created."
	@echo " "


run/build/nst_node.o: src/nst/node.cpp src/nst/node.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/node.cpp -o run/build/nst_node.o
	@echo "run/build/nst_node.o created."
	@echo " "


run/build/nst_state.o: src/nst/state.cpp src/nst/state.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/state.cpp -o run/build/nst_state.o
	@echo "run/build/nst_state.o created."
	@echo " "


run/build/nst_tank.o: src/nst/tank.cpp src/nst/tank.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/tank.cpp -o run/build/nst_tank.o
	@echo "run/build/nst_tank.o created."
	@echo " "


run/build/nst_tube.o: src/nst/tube.cpp src/nst/tube.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/tube.cpp -o run/build/nst_tube.o
	@echo "run/build/nst_tube.o created."
	@echo " "


run/build/output-raster_cairo.o: src/output-raster/cairo.cpp src/output-raster/cairo.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-raster/cairo.cpp -o run/build/output-raster_cairo.o
	@echo "run/build/output-raster_cairo.o created."
	@echo " "


run/build/output-raster_flow.o: src/output-raster/flow.cpp src/output-raster/flow.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-raster/flow.cpp -o run/build/output-raster_flow.o
	@echo "run/build/output-raster_flow.o created."
	@echo " "


run/build/output-vector_draw.o: src/output-vector/draw.cpp src/output-vector/draw.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-vector/draw.cpp -o run/build/output-vector_draw.o
	@echo "run/build/output-vector_draw.o created."
	@echo " "


run/build/output-vector_flow.o: src/output-vector/flow.cpp src/output-vector/flow.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-vector/flow.cpp -o run/build/output-vector_flow.o
	@echo "run/build/output-vector_flow.o created."
	@echo " "


run/build/output-vector_label-node.o: src/output-vector/label-node.cpp src/output-vector/label-node.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-vector/label-node.cpp -o run/build/output-vector_label-node.o
	@echo "run/build/output-vector_label-node.o created."
	@echo " "


run/build/output-vector_label-tube.o: src/output-vector/label-tube.cpp src/output-vector/label-tube.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-vector/label-tube.cpp -o run/build/output-vector_label-tube.o
	@echo "run/build/output-vector_label-tube.o created."
	@echo " "


run/build/output-vector_tikz.o: src/output-vector/tikz.cpp src/output-vector/tikz.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output-vector/tikz.cpp -o run/build/output-vector_tikz.o
	@echo "run/build/output-vector_tikz.o created."
	@echo " "


run/build/output_latex.o: src/output/latex.cpp src/output/latex.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output/latex.cpp -o run/build/output_latex.o
	@echo "run/build/output_latex.o created."
	@echo " "


run/build/output_property.o: src/output/property.cpp src/output/property.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output/property.cpp -o run/build/output_property.o
	@echo "run/build/output_property.o created."
	@echo " "


run/build/output_result.o: src/output/result.cpp src/output/result.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output/result.cpp -o run/build/output_result.o
	@echo "run/build/output_result.o created."
	@echo " "


run/build/output_visual-dimension.o: src/output/visual-dimension.cpp src/output/visual-dimension.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/output/visual-dimension.cpp -o run/build/output_visual-dimension.o
	@echo "run/build/output_visual-dimension.o created."
	@echo " "


run/build/program_debug-flow.o: src/program/debug-flow.cpp src/program/debug-flow.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/program/debug-flow.cpp -o run/build/program_debug-flow.o
	@echo "run/build/program_debug-flow.o created."
	@echo " "


run/build/program_flow-in-periodic-medium.o: src/program/flow-in-periodic-medium.cpp src/program/flow-in-periodic-medium.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/program/flow-in-periodic-medium.cpp -o run/build/program_flow-in-periodic-medium.o
	@echo "run/build/program_flow-in-periodic-medium.o created."
	@echo " "


run/build/program_function-trial.o: src/program/function-trial.cpp src/program/function-trial.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/program/function-trial.cpp -o run/build/program_function-trial.o
	@echo "run/build/program_function-trial.o created."
	@echo " "


run/build/simulate_menu.o: src/simulate/menu.cpp src/simulate/menu.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/menu.cpp -o run/build/simulate_menu.o
	@echo "run/build/simulate_menu.o created."
	@echo " "


run/build/simulate_property.o: src/simulate/property.cpp src/simulate/property.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/property.cpp -o run/build/simulate_property.o
	@echo "run/build/simulate_property.o created."
	@echo " "


run/build/simulate_step0-preparation.o: src/simulate/step0-preparation.cpp src/simulate/step0-preparation.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step0-preparation.cpp -o run/build/simulate_step0-preparation.o
	@echo "run/build/simulate_step0-preparation.o created."
	@echo " "


run/build/simulate_step1-tube-flow-coefficient.o: src/simulate/step1-tube-flow-coefficient.cpp src/simulate/step1-tube-flow-coefficient.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step1-tube-flow-coefficient.cpp -o run/build/simulate_step1-tube-flow-coefficient.o
	@echo "run/build/simulate_step1-tube-flow-coefficient.o created."
	@echo " "


run/build/simulate_step10-measure.o: src/simulate/step10-measure.cpp src/simulate/step10-measure.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step10-measure.cpp -o run/build/simulate_step10-measure.o
	@echo "run/build/simulate_step10-measure.o created."
	@echo " "


run/build/simulate_step2-pressure.o: src/simulate/step2-pressure.cpp src/simulate/step2-pressure.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step2-pressure.cpp -o run/build/simulate_step2-pressure.o
	@echo "run/build/simulate_step2-pressure.o created."
	@echo " "


run/build/simulate_step3-velocity.o: src/simulate/step3-velocity.cpp src/simulate/step3-velocity.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step3-velocity.cpp -o run/build/simulate_step3-velocity.o
	@echo "run/build/simulate_step3-velocity.o created."
	@echo " "


run/build/simulate_step4-time-step.o: src/simulate/step4-time-step.cpp src/simulate/step4-time-step.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step4-time-step.cpp -o run/build/simulate_step4-time-step.o
	@echo "run/build/simulate_step4-time-step.o created."
	@echo " "


run/build/simulate_step5-displacement.o: src/simulate/step5-displacement.cpp src/simulate/step5-displacement.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step5-displacement.cpp -o run/build/simulate_step5-displacement.o
	@echo "run/build/simulate_step5-displacement.o created."
	@echo " "


run/build/simulate_step6-pour-into-node.o: src/simulate/step6-pour-into-node.cpp src/simulate/step6-pour-into-node.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step6-pour-into-node.cpp -o run/build/simulate_step6-pour-into-node.o
	@echo "run/build/simulate_step6-pour-into-node.o created."
	@echo " "


run/build/simulate_step7-inject-evacuate.o: src/simulate/step7-inject-evacuate.cpp src/simulate/step7-inject-evacuate.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step7-inject-evacuate.cpp -o run/build/simulate_step7-inject-evacuate.o
	@echo "run/build/simulate_step7-inject-evacuate.o created."
	@echo " "


run/build/simulate_step8-distribute.o: src/simulate/step8-distribute.cpp src/simulate/step8-distribute.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step8-distribute.cpp -o run/build/simulate_step8-distribute.o
	@echo "run/build/simulate_step8-distribute.o created."
	@echo " "


run/build/simulate_step9-update-tube-mpos.o: src/simulate/step9-update-tube-mpos.cpp src/simulate/step9-update-tube-mpos.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step9-update-tube-mpos.cpp -o run/build/simulate_step9-update-tube-mpos.o
	@echo "run/build/simulate_step9-update-tube-mpos.o created."
	@echo " "


run/build/simulate_utility.o: src/simulate/utility.cpp src/simulate/utility.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/utility.cpp -o run/build/simulate_utility.o
	@echo "run/build/simulate_utility.o created."
	@echo " "


run/build/utility_math.o: src/utility/math.cpp src/utility/math.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/utility/math.cpp -o run/build/utility_math.o
	@echo "run/build/utility_math.o created."
	@echo " "


run/build/utility_measure.o: src/utility/measure.cpp src/utility/measure.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/utility/measure.cpp -o run/build/utility_measure.o
	@echo "run/build/utility_measure.o created."
	@echo " "


run/build/utility_random.o: src/utility/random.cpp src/utility/random.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/utility/random.cpp -o run/build/utility_random.o
	@echo "run/build/utility_random.o created."
	@echo " "


run/build/utility_str.o: src/utility/str.cpp src/utility/str.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/utility/str.cpp -o run/build/utility_str.o
	@echo "run/build/utility_str.o created."
	@echo " "


run/build/utility_time.o: src/utility/time.cpp src/utility/time.h src/global/decl.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/utility/time.cpp -o run/build/utility_time.o
	@echo "run/build/utility_time.o created."
	@echo " "
