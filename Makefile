TIMESTAMP := $(shell date +"%Y%m%d_%H%M%S")

all: necessary_compile run_program
	@echo "Command executed = all"


necessary_compile: folder_check run/incongen.exe run/process.exe run/simulate.exe
	@echo "Command executed = necessary_compile"


folder_check:
	rm -rf run/output
	mkdir -p run/
	mkdir -p run/build/
	mkdir -p run/input
	mkdir -p run/output
	mkdir -p run/output-old
	mkdir -p run/output/simulation-data
	mkdir -p run/output/simulation-calculations
	mkdir -p run/output/plots
	mkdir -p run/output/plots/pressure
	mkdir -p run/output/plots/velocity
	mkdir -p run/output/plots/fluids-nothick
	mkdir -p run/output/plots/fluids-thick
	mkdir -p run/output/plots/saturation
	@echo "Command executed = folder_check"


run_program: folder_check
	./run/incongen.exe
	./run/simulate.exe
	zip -r run/output-old/$(TIMESTAMP).zip run/output/


force: clean necessary_compile
	@echo "Command executed = force"


clean:
	rm -rf run/build/


edit:
	geany -i  src/drw/bmp.h src/drw/bmp.cpp src/dst/generator.h src/dst/generator.cpp src/dst/head.h src/exe/incongen.cpp src/exe/process.cpp src/exe/simulate.cpp src/incongen/manager.h src/incongen/manager.cpp src/io/fileplot.h src/io/fileplot.cpp src/io/fileread.h src/io/fileread.cpp src/io/filewrite.h src/io/filewrite.cpp src/io/head.h src/math/head.h src/network/dimension.h src/network/dimension.cpp src/networkfeature/mns.h src/networkfeature/mns.cpp src/process/manager.h src/process/manager.cpp src/process/viewfluids.h src/process/viewfluids.cpp src/simulate/manager.h src/simulate/manager.cpp


run/incongen.exe: run/build/exe_incongen.o run/build/drw_bmp.o run/build/dst_generator.o run/build/incongen_manager.o run/build/io_fileplot.o run/build/io_fileread.o run/build/io_filewrite.o run/build/network_dimension.o run/build/networkfeature_mns.o run/build/process_manager.o run/build/process_viewfluids.o run/build/simulate_manager.o
	g++  run/build/exe_incongen.o run/build/drw_bmp.o run/build/dst_generator.o run/build/incongen_manager.o run/build/io_fileplot.o run/build/io_fileread.o run/build/io_filewrite.o run/build/network_dimension.o run/build/networkfeature_mns.o run/build/process_manager.o run/build/process_viewfluids.o run/build/simulate_manager.o -o run/incongen.exe
	@echo "run/incongen.exe created."


run/process.exe: run/build/exe_process.o run/build/drw_bmp.o run/build/dst_generator.o run/build/incongen_manager.o run/build/io_fileplot.o run/build/io_fileread.o run/build/io_filewrite.o run/build/network_dimension.o run/build/networkfeature_mns.o run/build/process_manager.o run/build/process_viewfluids.o run/build/simulate_manager.o
	g++  run/build/exe_process.o run/build/drw_bmp.o run/build/dst_generator.o run/build/incongen_manager.o run/build/io_fileplot.o run/build/io_fileread.o run/build/io_filewrite.o run/build/network_dimension.o run/build/networkfeature_mns.o run/build/process_manager.o run/build/process_viewfluids.o run/build/simulate_manager.o -o run/process.exe
	@echo "run/process.exe created."


run/simulate.exe: run/build/exe_simulate.o run/build/drw_bmp.o run/build/dst_generator.o run/build/incongen_manager.o run/build/io_fileplot.o run/build/io_fileread.o run/build/io_filewrite.o run/build/network_dimension.o run/build/networkfeature_mns.o run/build/process_manager.o run/build/process_viewfluids.o run/build/simulate_manager.o
	g++  run/build/exe_simulate.o run/build/drw_bmp.o run/build/dst_generator.o run/build/incongen_manager.o run/build/io_fileplot.o run/build/io_fileread.o run/build/io_filewrite.o run/build/network_dimension.o run/build/networkfeature_mns.o run/build/process_manager.o run/build/process_viewfluids.o run/build/simulate_manager.o -o run/simulate.exe
	@echo "run/simulate.exe created."


run/build/drw_bmp.o: src/drw/bmp.h src/drw/bmp.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/drw/bmp.cpp -o run/build/drw_bmp.o
	@echo "run/build/drw_bmp.o created."


run/build/dst_generator.o: src/dst/generator.h src/dst/generator.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/dst/generator.cpp -o run/build/dst_generator.o
	@echo "run/build/dst_generator.o created."


run/build/exe_incongen.o: src/exe/incongen.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/incongen.cpp -o run/build/exe_incongen.o
	@echo "run/build/exe_incongen.o created."


run/build/exe_process.o: src/exe/process.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/process.cpp -o run/build/exe_process.o
	@echo "run/build/exe_process.o created."


run/build/exe_simulate.o: src/exe/simulate.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/exe/simulate.cpp -o run/build/exe_simulate.o
	@echo "run/build/exe_simulate.o created."


run/build/incongen_manager.o: src/incongen/manager.h src/incongen/manager.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/incongen/manager.cpp -o run/build/incongen_manager.o
	@echo "run/build/incongen_manager.o created."


run/build/io_fileplot.o: src/io/fileplot.h src/io/fileplot.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/io/fileplot.cpp -o run/build/io_fileplot.o
	@echo "run/build/io_fileplot.o created."


run/build/io_fileread.o: src/io/fileread.h src/io/fileread.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/io/fileread.cpp -o run/build/io_fileread.o
	@echo "run/build/io_fileread.o created."


run/build/io_filewrite.o: src/io/filewrite.h src/io/filewrite.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/io/filewrite.cpp -o run/build/io_filewrite.o
	@echo "run/build/io_filewrite.o created."


run/build/network_dimension.o: src/network/dimension.h src/network/dimension.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/network/dimension.cpp -o run/build/network_dimension.o
	@echo "run/build/network_dimension.o created."


run/build/networkfeature_mns.o: src/networkfeature/mns.h src/networkfeature/mns.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/networkfeature/mns.cpp -o run/build/networkfeature_mns.o
	@echo "run/build/networkfeature_mns.o created."


run/build/process_manager.o: src/process/manager.h src/process/manager.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/process/manager.cpp -o run/build/process_manager.o
	@echo "run/build/process_manager.o created."


run/build/process_viewfluids.o: src/process/viewfluids.h src/process/viewfluids.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/process/viewfluids.cpp -o run/build/process_viewfluids.o
	@echo "run/build/process_viewfluids.o created."


run/build/simulate_manager.o: src/simulate/manager.h src/simulate/manager.cpp src/dst/head.h src/io/head.h src/math/head.h
	g++ -c -Wall -std=c++17 -Isrc/ src/simulate/manager.cpp -o run/build/simulate_manager.o
	@echo "run/build/simulate_manager.o created."
