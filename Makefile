

all: folder_check compile_necessary run_program
	@echo "Command executed = all"
	@echo " "


folder_check:
	mkdir -p src/
	mkdir -p src/exe/
	mkdir -p src/global/
	mkdir -p run/
	mkdir -p run/build/
	mkdir -p run/results/
	@echo "Command executed = folder_check"
	@echo " "


compile_necessary: run/simulate.exe
	@echo "Command executed = compile_necessary"
	@echo " "


run_program:
	rm -rf run/results/*
	./run/simulate.exe


force: folder_check clear_build compile_necessary run_program
	@echo "Command executed = force"
	@echo " "


clear_build:
	rm -rf run/build/*
	@echo "Command executed = force"
	@echo " "


edit:
	geany -i  src/exe/simulate.cpp src/global/dst.h src/ic/displacement-test.cpp src/ic/displacement-test.h src/ic/flow-visualization.cpp src/ic/flow-visualization.h src/io/file-write.cpp src/io/file-write.h src/nst/node.cpp src/nst/node.h src/nst/state.cpp src/nst/state.h src/nst/tube.cpp src/nst/tube.h src/simulate/menu.cpp src/simulate/menu.h src/simulate/physics.cpp src/simulate/physics.h src/simulate/step-preparation.cpp src/simulate/step-preparation.h src/simulate/step1-pressure.cpp src/simulate/step1-pressure.h src/simulate/step2-flow-rate.cpp src/simulate/step2-flow-rate.h src/simulate/step3-velocity.cpp src/simulate/step3-velocity.h src/simulate/step4-time-step.cpp src/simulate/step4-time-step.h src/simulate/step5-integration.cpp src/simulate/step5-integration.h src/utility/math.cpp src/utility/math.h src/utility/measure.cpp src/utility/measure.h src/utility/random.cpp src/utility/random.h src/visualize/draw.cpp src/visualize/draw.h src/visualize/flow.cpp src/visualize/flow.h src/visualize/latex.cpp src/visualize/latex.h src/visualize/menu.cpp src/visualize/menu.h src/visualize/re-scale-state-for-plot.cpp src/visualize/re-scale-state-for-plot.h


run/simulate.exe: run/build/exe_simulate.o run/build/ic_displacement-test.o run/build/ic_flow-visualization.o run/build/io_file-write.o run/build/nst_node.o run/build/nst_state.o run/build/nst_tube.o run/build/simulate_menu.o run/build/simulate_physics.o run/build/simulate_step-preparation.o run/build/simulate_step1-pressure.o run/build/simulate_step2-flow-rate.o run/build/simulate_step3-velocity.o run/build/simulate_step4-time-step.o run/build/simulate_step5-integration.o run/build/utility_math.o run/build/utility_measure.o run/build/utility_random.o run/build/visualize_draw.o run/build/visualize_flow.o run/build/visualize_latex.o run/build/visualize_menu.o run/build/visualize_re-scale-state-for-plot.o
	g++  run/build/exe_simulate.o run/build/ic_displacement-test.o run/build/ic_flow-visualization.o run/build/io_file-write.o run/build/nst_node.o run/build/nst_state.o run/build/nst_tube.o run/build/simulate_menu.o run/build/simulate_physics.o run/build/simulate_step-preparation.o run/build/simulate_step1-pressure.o run/build/simulate_step2-flow-rate.o run/build/simulate_step3-velocity.o run/build/simulate_step4-time-step.o run/build/simulate_step5-integration.o run/build/utility_math.o run/build/utility_measure.o run/build/utility_random.o run/build/visualize_draw.o run/build/visualize_flow.o run/build/visualize_latex.o run/build/visualize_menu.o run/build/visualize_re-scale-state-for-plot.o -o run/simulate.exe
	@echo "run/simulate.exe created."
	@echo " "


run/build/exe_simulate.o: src/exe/simulate.cpp src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/simulate.cpp -o run/build/exe_simulate.o
	@echo "run/build/exe_simulate.o created."
	@echo " "


run/build/ic_displacement-test.o: src/ic/displacement-test.cpp src/ic/displacement-test.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/ic/displacement-test.cpp -o run/build/ic_displacement-test.o
	@echo "run/build/ic_displacement-test.o created."
	@echo " "


run/build/ic_flow-visualization.o: src/ic/flow-visualization.cpp src/ic/flow-visualization.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/ic/flow-visualization.cpp -o run/build/ic_flow-visualization.o
	@echo "run/build/ic_flow-visualization.o created."
	@echo " "


run/build/io_file-write.o: src/io/file-write.cpp src/io/file-write.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/io/file-write.cpp -o run/build/io_file-write.o
	@echo "run/build/io_file-write.o created."
	@echo " "


run/build/nst_node.o: src/nst/node.cpp src/nst/node.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/node.cpp -o run/build/nst_node.o
	@echo "run/build/nst_node.o created."
	@echo " "


run/build/nst_state.o: src/nst/state.cpp src/nst/state.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/state.cpp -o run/build/nst_state.o
	@echo "run/build/nst_state.o created."
	@echo " "


run/build/nst_tube.o: src/nst/tube.cpp src/nst/tube.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/tube.cpp -o run/build/nst_tube.o
	@echo "run/build/nst_tube.o created."
	@echo " "


run/build/simulate_menu.o: src/simulate/menu.cpp src/simulate/menu.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/menu.cpp -o run/build/simulate_menu.o
	@echo "run/build/simulate_menu.o created."
	@echo " "


run/build/simulate_physics.o: src/simulate/physics.cpp src/simulate/physics.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/physics.cpp -o run/build/simulate_physics.o
	@echo "run/build/simulate_physics.o created."
	@echo " "


run/build/simulate_step-preparation.o: src/simulate/step-preparation.cpp src/simulate/step-preparation.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step-preparation.cpp -o run/build/simulate_step-preparation.o
	@echo "run/build/simulate_step-preparation.o created."
	@echo " "


run/build/simulate_step1-pressure.o: src/simulate/step1-pressure.cpp src/simulate/step1-pressure.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step1-pressure.cpp -o run/build/simulate_step1-pressure.o
	@echo "run/build/simulate_step1-pressure.o created."
	@echo " "


run/build/simulate_step2-flow-rate.o: src/simulate/step2-flow-rate.cpp src/simulate/step2-flow-rate.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step2-flow-rate.cpp -o run/build/simulate_step2-flow-rate.o
	@echo "run/build/simulate_step2-flow-rate.o created."
	@echo " "


run/build/simulate_step3-velocity.o: src/simulate/step3-velocity.cpp src/simulate/step3-velocity.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step3-velocity.cpp -o run/build/simulate_step3-velocity.o
	@echo "run/build/simulate_step3-velocity.o created."
	@echo " "


run/build/simulate_step4-time-step.o: src/simulate/step4-time-step.cpp src/simulate/step4-time-step.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step4-time-step.cpp -o run/build/simulate_step4-time-step.o
	@echo "run/build/simulate_step4-time-step.o created."
	@echo " "


run/build/simulate_step5-integration.o: src/simulate/step5-integration.cpp src/simulate/step5-integration.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/step5-integration.cpp -o run/build/simulate_step5-integration.o
	@echo "run/build/simulate_step5-integration.o created."
	@echo " "


run/build/utility_math.o: src/utility/math.cpp src/utility/math.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/utility/math.cpp -o run/build/utility_math.o
	@echo "run/build/utility_math.o created."
	@echo " "


run/build/utility_measure.o: src/utility/measure.cpp src/utility/measure.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/utility/measure.cpp -o run/build/utility_measure.o
	@echo "run/build/utility_measure.o created."
	@echo " "


run/build/utility_random.o: src/utility/random.cpp src/utility/random.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/utility/random.cpp -o run/build/utility_random.o
	@echo "run/build/utility_random.o created."
	@echo " "


run/build/visualize_draw.o: src/visualize/draw.cpp src/visualize/draw.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/visualize/draw.cpp -o run/build/visualize_draw.o
	@echo "run/build/visualize_draw.o created."
	@echo " "


run/build/visualize_flow.o: src/visualize/flow.cpp src/visualize/flow.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/visualize/flow.cpp -o run/build/visualize_flow.o
	@echo "run/build/visualize_flow.o created."
	@echo " "


run/build/visualize_latex.o: src/visualize/latex.cpp src/visualize/latex.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/visualize/latex.cpp -o run/build/visualize_latex.o
	@echo "run/build/visualize_latex.o created."
	@echo " "


run/build/visualize_menu.o: src/visualize/menu.cpp src/visualize/menu.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/visualize/menu.cpp -o run/build/visualize_menu.o
	@echo "run/build/visualize_menu.o created."
	@echo " "


run/build/visualize_re-scale-state-for-plot.o: src/visualize/re-scale-state-for-plot.cpp src/visualize/re-scale-state-for-plot.h src/global/dst.h
	g++ -c -Wall -std=c++17 -Isrc/ src/visualize/re-scale-state-for-plot.cpp -o run/build/visualize_re-scale-state-for-plot.o
	@echo "run/build/visualize_re-scale-state-for-plot.o created."
	@echo " "
