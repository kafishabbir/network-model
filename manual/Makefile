all:
	pdflatex -output-directory=output main
	biber output/main
	pdflatex -output-directory=output main
	clear
	pdflatex -output-directory=output main
	
edit:
	geany -i \
	main.tex \
	src/chapter01.tex \
	src/chapter02.tex \
	src/chapter03.tex \
	src/chapter04.tex \
	src/chapter05.tex \
	src/chapter06.tex \
	src/chapter07.tex \
	src/chapter08.tex

push:
	git add .
	git commit -m "upload"
	git push
	
