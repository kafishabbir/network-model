#include "menu.h"
#include "decl.h"

/*!
 * How the program makefilegen.exe works
 *
 * This is the folder structure of porous-media/network-model:
 * 		manual/
 * 		src/
 * 			lib(s)/
 * 			global/
 * 			exe/
 * 		makefilegen/
 * 			src/
 * 			build/
 * 			makefilegen-config.txt
 * 			Makefile
 * 		run/
 * 			build/
 * 			results/
 * 		Makefile
 *
 * at ~/porous-media/network-model/makefilegen$: make force
 * 		1. ./build/makefilegen.exe is created
 * 		2. ./makefilegen-config.txt -> ./build/makefilegen.exe = ./build/Makefile
 * 		3. mv build/Makefile ../
 * for only $: make, all except step one is performed
 *
 */

int main()
{
	// read ./makefile-gen/file-structure.txt
	const std::vector<std::string> file_vec = Menu::read_file_structure();

	// the output will be written to ./makefile-gen/build/Makefile
	std::ofstream fout(decl::target_output);


	/*
	 * all:
	 * 		folder_check
	 * 		compile_necessary
	 * 		run_program
	 */
	Menu::all(fout);

	/*
	 * src/
	 * makefilegen/
	 * run/
	 * run/build/
	 * run/results/
	 */
	Menu::folder_check(fout);

	/*
	 * compile_necessary:
	 * 		run/ext1
	 * 		run/exe2
	 *
	 */
	Menu::compile_necessary(fout, file_vec);


	/*
	 * run:
	 * 		rm -rf run/results/*
	 * 		./run/exe1
	 */
	Menu::run_program(fout);


	/*
	 * force:
	 *		folder_check
	 * 		rm -rf run/build/*
	 * 		compile_necessary
	 * 		run_program
	 */
	Menu::force(fout);


	Menu::clear_build(fout);

	/*
	 * geany -i src/lib/lib.h src/lib/lib.cpp
	 */
	Menu::edit(fout, file_vec);

	/*
	 * exe1: obj1.o obj2.o exe1.o
	 * 		g++ a.o b.o -o run/exe1
	 */
	Menu::exe(fout, file_vec);

	/*
	 * build/obj1.o: obj1.cpp obj1.h global-headers.h
	 * 		g++ -c Wall -o build/obj1.o
	 */
	Menu::object(fout, file_vec);

	return 0;
}
