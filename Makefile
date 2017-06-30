all:
	gcc -o t2 src/*.c -I./include -Wall;\
	mkdir -p saidas
run:
	./t2
clear:
	rm saidas/*.bin t2
