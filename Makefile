all:
	gcc -o t2 src/*.c -I./include -Wall;\
	mkdir -p saidas indices
run:
	./t2
clear:
	rm saidas/*.bin t2 indices/*.bin
