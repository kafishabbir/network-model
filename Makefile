

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
	geany -i  src/exe/simulate.cpp src/global/constants.h src/global/filenames.h src/print/helloworld.h src/print/helloworld.cpp


run/simulate.exe: run/build/exe_simulate.o run/build/print_helloworld.o
	g++  run/build/exe_simulate.o run/build/print_helloworld.o -o run/simulate.exe
	@echo "run/simulate.exe created."
	@echo " "


run/build/exe_simulate.o: src/exe/simulate.cpp src/global/constants.h src/global/filenames.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/simulate.cpp -o run/build/exe_simulate.o
	@echo "run/build/exe_simulate.o created."
	@echo " "


run/build/print_helloworld.o: src/print/helloworld.h src/print/helloworld.cpp src/global/constants.h src/global/filenames.h
	g++ -c -Wall -std=c++17 -Isrc/ src/print/helloworld.cpp -o run/build/print_helloworld.o
	@echo "run/build/print_helloworld.o created."
	@echo " "
