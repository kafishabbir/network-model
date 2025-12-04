

all: print_one_empty_line folder_check compile_necessary run_program
	@echo "Command executed = all"


folder_check: print_one_empty_line
	mkdir -p src/
	mkdir -p src/exe/
	mkdir -p src/global/
	mkdir -p run/
	mkdir -p run/build/
	mkdir -p run/results/
	@echo "Command executed = folder_check"


compile_necessary: print_one_empty_line run/simulate.exe
	@echo "Command executed = compile_necessary"


run_program: print_one_empty_line
	rm -rf run/results/*
	./run/simulate.exe


force: print_one_empty_line folder_check clear_build compile_necessary run_program
	@echo "Command executed = force"


clear_build: print_one_empty_line
	rm -rf run/build/*
	@echo "Command executed = force"


print_one_empty_line:
	@echo " "


edit: print_one_empty_line
	geany -i  src/exe/simulate.cpp src/global/constants.h src/global/filenames.h src/print/helloworld.h src/print/helloworld.cpp


run/simulate.exe: print_one_empty_line run/build/exe_simulate.o run/build/print_helloworld.o
	g++  run/build/exe_simulate.o run/build/print_helloworld.o -o run/simulate.exe
	@echo "run/simulate.exe created."


run/build/exe_simulate.o: print_one_empty_line src/exe/simulate.cpp src/global/constants.h src/global/filenames.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/simulate.cpp -o run/build/exe_simulate.o
	@echo "run/build/exe_simulate.o created."


run/build/print_helloworld.o: print_one_empty_line src/print/helloworld.h src/print/helloworld.cpp src/global/constants.h src/global/filenames.h
	g++ -c -Wall -std=c++17 -Isrc/ src/print/helloworld.cpp -o run/build/print_helloworld.o
	@echo "run/build/print_helloworld.o created."
