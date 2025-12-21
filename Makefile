

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
	geany -i  src/exe/simulate.cpp src/generator/ic.h src/generator/ic.cpp src/global/constants.h src/global/dst.h src/global/filenames.h src/nst/node.h src/nst/node.cpp src/nst/tube.h src/nst/tube.cpp src/plot/filepath.h src/plot/filepath.cpp src/plot/flow.h src/plot/flow.cpp src/plot/latexcode.h src/plot/latexcode.cpp src/print/helloworld.h src/print/helloworld.cpp


run/simulate.exe: run/build/exe_simulate.o run/build/generator_ic.o run/build/nst_node.o run/build/nst_tube.o run/build/plot_filepath.o run/build/plot_flow.o run/build/plot_latexcode.o run/build/print_helloworld.o
	g++  run/build/exe_simulate.o run/build/generator_ic.o run/build/nst_node.o run/build/nst_tube.o run/build/plot_filepath.o run/build/plot_flow.o run/build/plot_latexcode.o run/build/print_helloworld.o -o run/simulate.exe
	@echo "run/simulate.exe created."
	@echo " "


run/build/exe_simulate.o: src/exe/simulate.cpp src/global/constants.h src/global/dst.h src/global/filenames.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/simulate.cpp -o run/build/exe_simulate.o
	@echo "run/build/exe_simulate.o created."
	@echo " "


run/build/generator_ic.o: src/generator/ic.h src/generator/ic.cpp src/global/constants.h src/global/dst.h src/global/filenames.h
	g++ -c -Wall -std=c++17 -Isrc/ src/generator/ic.cpp -o run/build/generator_ic.o
	@echo "run/build/generator_ic.o created."
	@echo " "


run/build/nst_node.o: src/nst/node.h src/nst/node.cpp src/global/constants.h src/global/dst.h src/global/filenames.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/node.cpp -o run/build/nst_node.o
	@echo "run/build/nst_node.o created."
	@echo " "


run/build/nst_tube.o: src/nst/tube.h src/nst/tube.cpp src/global/constants.h src/global/dst.h src/global/filenames.h
	g++ -c -Wall -std=c++17 -Isrc/ src/nst/tube.cpp -o run/build/nst_tube.o
	@echo "run/build/nst_tube.o created."
	@echo " "


run/build/plot_filepath.o: src/plot/filepath.h src/plot/filepath.cpp src/global/constants.h src/global/dst.h src/global/filenames.h
	g++ -c -Wall -std=c++17 -Isrc/ src/plot/filepath.cpp -o run/build/plot_filepath.o
	@echo "run/build/plot_filepath.o created."
	@echo " "


run/build/plot_flow.o: src/plot/flow.h src/plot/flow.cpp src/global/constants.h src/global/dst.h src/global/filenames.h
	g++ -c -Wall -std=c++17 -Isrc/ src/plot/flow.cpp -o run/build/plot_flow.o
	@echo "run/build/plot_flow.o created."
	@echo " "


run/build/plot_latexcode.o: src/plot/latexcode.h src/plot/latexcode.cpp src/global/constants.h src/global/dst.h src/global/filenames.h
	g++ -c -Wall -std=c++17 -Isrc/ src/plot/latexcode.cpp -o run/build/plot_latexcode.o
	@echo "run/build/plot_latexcode.o created."
	@echo " "


run/build/print_helloworld.o: src/print/helloworld.h src/print/helloworld.cpp src/global/constants.h src/global/dst.h src/global/filenames.h
	g++ -c -Wall -std=c++17 -Isrc/ src/print/helloworld.cpp -o run/build/print_helloworld.o
	@echo "run/build/print_helloworld.o created."
	@echo " "
